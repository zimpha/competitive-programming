#include "highest_mountain.h"
#include "message.h"
#include <cstdio>
#include <vector>
#include <utility>

typedef long long ll;
using namespace std;
vector<pair<int, ll>> convex;
int cbeg;
int cend;
int prev_elements;  // 0

const char kQuery = 'q';
const char kBack = 'b';
const char kForward = 'f';
const char kEnd = 'e';

#define CHUNK_SIZE 1000

// The goal of the "Drive" method is to reconcile our convex hull with the
// convex hull of the guy after us ("next"). We do this by trying to find a
// tangent line to both our hulls. If this line goes through the "warden" (that
// is, it bypasses all our points), we will relinquish control to "prev" and let
// our predecessor do the driving. If not, we let our successor drive. This
// operation can cause some points to drop out from our set from the right
// (which we represent by decreasing "cend").
void Drive(int prev, int next) {
  // To merge two convex hulls, we do a moral equivalent of a ternary search.
  // So, in an ideal (zero-time-message-passing) world, we'd send a pair of
  // points to our successor, and eliminate a third of the interval.
  // However, the message passing is not zero-cost, so we optimize by sending a
  // group of points (an equidivision of our set of points), and we will get
  // back the information "out of these points, _this_ one is the one the
  // tangent line passes through". This means the real answer is in one of the
  // intervals adjacent to this point. If there is more than one candidate point
  // at this moment, rinse and repeat.
  vector<int> chunk;
  // Now, push the elements in our convex hull at the other guy.
  int cleft = cbeg;
  int cright = cend;
  // In each loop, we know the answer is in [cleft, cright).
  while (cright - cleft > 1) {
    chunk.clear();
    // We can just send all of our points.
    if (cright - cleft <= CHUNK_SIZE) {
      for (int i = cleft; i < cright; ++i) {
        chunk.push_back(i);
      }
    } else {
      // Equally spaced points, containing the cleft and cright - 1.
      for (int i = 0; i < CHUNK_SIZE; ++i) {
        int pos = cleft + ((cright - cleft - 1) * (ll) i) / (CHUNK_SIZE - 1);
        chunk.push_back(pos);
      }
    }
    PutChar(next, kQuery);
    PutInt(next, chunk.size());
    for (int i = 0; i < chunk.size(); ++i) {
      PutInt(next, convex[chunk[i]].first);
    }
    Send(next);
    // The guy after us will now tell us which of our points is the last one in
    // our common convex hull.
    Receive(next);
    int pos_in_chunk = GetInt(next);
    // So, we know the real point of tangency is somewhere between the left and
    // right neighbour of the point we got back (it's neither of them).
    if (pos_in_chunk != 0) {
      cleft = chunk[pos_in_chunk - 1] + 1;
    }
    if (pos_in_chunk != chunk.size() - 1) {
      cright = chunk[pos_in_chunk + 1];
      // Also, as an aside, we can throw out the points to the right from the
      // game.
      cend = cright;
    }
  }
  // One case is we're left with the warden in hand. In this case, none of
  // our points will make it to the convex hull. We're out of the game, and
  // our predecessor gets to drive.
  if (cleft == cbeg && MyNodeId() != 0) {
    PutChar(prev, kBack);
    PutInt(prev, next);
    Send(prev);
    return;
  }
  // Otherwise, we still have some of our convex hull elements in the game.
  // Driving moves on to the guy after us. We tell him how many elements of the
  // convex hull are before him, and what's the last element of the convex hull
  // before him.
  PutChar(next, kForward);
  PutInt(next, prev_elements + cend - cbeg - 1);
  PutInt(next, convex[cleft].first);
  Send(next);
  return;
}

// Positive means P0 is under (to the right) of the P1->P2 line.
ll Dist(const pair<int, ll> &P1, const pair<int, ll> &P2,
        const pair<int, ll> &P0) {
  return P0.first * (P2.second - P1.second) -
         P0.second * (P2.first - P1.first) + P2.first * P1.second -
         P2.second * P1.first;
}

// Does the line P1, P2 cut our polygon, or is it tangent/outside it?
bool Cuts(const pair<int, ll> &P1, const pair<int, ll> &P2) {
  int left = cbeg;
  int right = cend;
  while (right - left > 2) {
    int c1 = (2 * left + right) / 3;
    int c2 = (left + 2 * right) / 3;
    ll d1 = Dist(P1, P2, convex[c1]);
    ll d2 = Dist(P1, P2, convex[c2]);
    if (d1 < 0 || d2 < 0) return true;
    if (d1 > d2) {
      left = c1;
    } else {
      right = c2;
    }
  }
  for (int i = left; i < right; ++i) {
    if (Dist(P1, P2, convex[i]) < 0) return true;
  }
  return false;
}

// The query method is the "answer" part of the drive method. The "who" node
// sends us a set of points, and wants to know which one of them will be a part
// of the common tangent line.
// We assume we can retrieve the whole matrix (in the format "size, elements")
// from the message.
void Query(int who) {
  int hleft = 0;
  int hright = GetInt(who);
  vector<pair<int, ll>> h;
  for (int i = 0; i < hright; ++i) {
    int x = GetInt(who);
    h.push_back(make_pair(x, (ll)GetHeight(x)));
  }
  // Right now, I have two convex hulls, and I want to merge them. Observe a
  // line formed by two adjacent points in the "input" polygon. If this line
  // cuts the right polygon, we know the right of the two adjacent points is
  // below the convex hull. Otherwise, we know the left point is below the
  // tangent line.
  while (hright - hleft > 1) {
    int hmed = (hright + hleft - 2) / 2;
    if (Cuts(h[hmed], h[hmed + 1])) {
      hright = hmed + 1;
    } else {
      hleft = hmed + 1;
    }
  }
  PutInt(who, hleft);
  Send(who);
}

// Calculate my own convex hull.
void DoConvex(ll mybeg, ll myend) {
  cbeg = 1;
  cend = 1;
  prev_elements = 0;
  // A placeholder for a "warden" from the previous batch.
  convex.push_back(make_pair(-1, -1LL));
  if (myend - mybeg < 2) {
    for (int i = mybeg; i < myend; ++i) {
      convex.push_back(make_pair(i, GetHeight(i)));
      cend++;
    }
  } else {
    convex.push_back(make_pair(mybeg, GetHeight(mybeg)));
    convex.push_back(make_pair(mybeg + 1, GetHeight(mybeg + 1)));
    cend = 3;
    for (int i = mybeg + 2; i < myend; ++i) {
      ll h = GetHeight(i);
      while (cend > 2) {
        int x1 = convex[cend - 1].first - convex[cend - 2].first;
        int x2 = i - convex[cend - 2].first;
        ll y1 = convex[cend - 1].second - convex[cend - 2].second;
        ll y2 = h - convex[cend - 2].second;
        if (x1 * y2 > x2 * y1) {
          cend -= 1;
          convex.pop_back();
        } else {
          break;
        }
      }
      cend += 1;
      convex.push_back(make_pair(i, h));
    }
  }
}

void InsertWarden(int warden_pos) {
  auto warden = make_pair(warden_pos, (ll)(GetHeight(warden_pos)));
  int left = cbeg;
  int right = cend - 2;
  if (Dist(warden, convex[left], convex[left + 1]) >= 0) {
    convex[--cbeg] = warden;
    return;
  }
  if (Dist(warden, convex[right], convex[right + 1]) < 0) {
    convex[right] = warden;
    cbeg = right;
    return;
  }
  while (right - left > 1) {
    int med = (left + right) / 2;
    if (Dist(warden, convex[med], convex[med + 1]) < 0) {
      left = med;
    } else {
      right = med;
    }
  }
  convex[left] = warden;
  cbeg = left;
}

int main() {
  ll N = NumberOfPeaks();
  // Just to make sure everyone has a non-empty slice.
  if (N < 1000) {
    if (MyNodeId() != 0) {
      return 0;
    } else {
      DoConvex(0, N);
      printf("%zd\n", convex.size() - 1);
      return 0;
    }
  }
  ll mybeg = N * MyNodeId() / NumberOfNodes();
  ll myend = N * (MyNodeId() + 1) / NumberOfNodes();
  DoConvex(mybeg, myend);
  int previous_node = -1;
  int next_node = MyNodeId() + 1;

  if (MyNodeId() != 0) {
    while (true) {
      int source = Receive(-1);
      char c = GetChar(source);
      if (c == kQuery) {
        Query(source);
      } else {
        assert(c == kForward);
        previous_node = source;
        prev_elements = GetInt(source);
        int warden = GetInt(source);
        InsertWarden(warden);
        break;
      }
    }
  }
  // If we're the last node, the whole convex hull is calculated at this point.
  if (MyNodeId() == NumberOfNodes() - 1) {
    for (int i = 0; i < NumberOfNodes() - 1; ++i) {
      PutChar(i, kEnd);
      Send(i);
    }
    printf("%d\n", prev_elements + cend - cbeg);
    return 0;
  }
  Drive(previous_node, next_node);
  // At this point, we either told someone in front to drive, or we told someone
  // in the back to drive and then skip us. Regardless, the next request will
  // come from the front, and will either be a request to drive, or a request to
  // end.
  while (true) {
    int source = Receive(-1);
    char c = GetChar(source);
    if (c == kEnd) return 0;
    assert(c == kBack);
    next_node = GetInt(source);
    Drive(previous_node, next_node);
  }
  return 0;
}

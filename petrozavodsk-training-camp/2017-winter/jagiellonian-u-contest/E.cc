#include <cstdio>
#include <cassert>
#include <vector>
#include <array>
#include <set>
#include <queue>
#include <algorithm>

const int N = 4e5 + 10, inf = 2e9 + 10;

std::array<int, 3> ev[N];

struct Node {
  int l, r, t;
  bool operator < (const Node &rhs) const {
    if (rhs.r == inf) return l - (rhs.t - t) < rhs.l;
    else if (r == inf) return l < rhs.l - (t - rhs.t);
    else return l < rhs.l;
  }
};

struct Merge {
  int t;
  std::set<Node>::iterator it;
  Merge(int t, std::set<Node>::iterator it): t(t), it(it) {}
  bool operator < (const Merge &rhs) const {
    return t < rhs.t || (t == rhs.t && it->l > rhs.it->l);
  }
};

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, m;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
      scanf("%d%d%d", &ev[i][0], &ev[i][2], &ev[i][1]);
      ev[i][1] = -ev[i][1];
    }
    scanf("%d", &m);
    for (int i = 0; i < m; ++i) {
      scanf("%d%d", &ev[i + n][0], &ev[i + n][2]);
      ev[i + n][1] = i;
    }
    std::sort(ev, ev + n + m);
    std::vector<int> ret(m);
    std::set<Node> segs;
    std::set<Merge> merge;

    segs.insert((Node){0, 0, 0});

    auto get_time = [] (int r, int rt, int l, int lt) {
      // r + (t - rt) + 1 >= l - (t - lt)
      // t >= ceil((l + lt - r + rt - 1) / 2)
      return (l + lt - r + rt) / 2;
    };

    auto erase = [&] (std::set<Node>::iterator o) {
      auto lo = segs.end(), ro = segs.end();
      if (o != segs.begin()) {
        lo = std::prev(o);
        int t = get_time(lo->r, lo->t, o->l, o->t);
        merge.erase((Merge){t, lo});
      }
      if (std::next(o) != segs.end()) {
        ro = std::next(o);
        int t = get_time(o->r, o->t, ro->l, ro->t);
        merge.erase((Merge){t, o});
      }
      if (lo != segs.end() && ro != segs.end()) {
        int t = get_time(lo->r, lo->t, ro->l, ro->t);
        merge.emplace(t, lo);
      }
      return segs.erase(o);
    };

    auto add_seg = [&](int l, int r, int t) {
      auto o = segs.insert((Node){l, r, t}).first;
      auto lo = segs.end(), ro = std::next(o);
      if (o != segs.begin()) lo = std::prev(o);
      if (lo != segs.end() && ro != segs.end()) {
        int t = get_time(lo->r, lo->t, ro->l, ro->t);
        merge.erase((Merge){t, lo});
      }
      if (lo != segs.end()) {
        int t = get_time(lo->r, lo->t, o->l, o->t);
        merge.emplace(t, lo);
      }
      if (ro != segs.end()) {
        int t = get_time(o->r, o->t, ro->l, ro->t);
        merge.emplace(t, o);
      }
    };

    for (int i = 0; i < n + m; ++i) {
      int ts = ev[i][0], x = ev[i][2];
      while (!merge.empty() && merge.begin()->t <= ts) {
        auto ia = merge.begin()->it, ib = std::next(ia);
        int t = merge.begin()->t;
        int l = ia->l - (t - ia->t);
        int r = ib->r + (t - ib->t);
        erase(ia); erase(ib);
        add_seg(l, r, t);
      }
      if (ev[i][1] < 0) { // erase
        int d = -ev[i][1];
        int l = x - d + 1, r = x + d - 1;
        auto it = segs.upper_bound((Node){l, inf, ts});
        if (it != segs.begin()) it = std::prev(it);
        std::vector<std::pair<int, int>> vs;
        for (; it != segs.end(); ) {
          int ll = it->l - (ts - it->t), rr = it->r + (ts - it->t);
          if (ll > r) break;
          if (std::max(ll, l) <= std::min(rr, r)) {
            if (ll < l) vs.emplace_back(ll, l - 1);
            if (r < rr) vs.emplace_back(r + 1, rr);
            it = erase(it);
          } else ++it;
        }
        for (auto &e: vs) {
          add_seg(e.first, e.second, ts);
        }
      } else { // query
        auto it = segs.upper_bound((Node){x, inf, ts});
        if (it != segs.begin()) {
          //printf("q %d=%d %d %d\n", x, it->l - (ts - it->t), it->r + (ts - it->t), it->t);
          it = std::prev(it);
          ret[ev[i][1]] |= it->l - (ts - it->t) <= x && x <= it->r + (ts - it->t);
        }
      }
      //printf("t=%d: ", ts);
      //for (auto &e: segs) {
      //  printf("[%d, %d] ", e.l - (ts - e.t), e.r + (ts - e.t));
      //}
      //puts("");
    }
    for (int i = 0; i < m; ++i) putchar("*@"[ret[i]]);
    puts("");
  }
  return 0;
}

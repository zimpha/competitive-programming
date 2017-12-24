// http://www.spoj.com/problems/BOI7FEN/
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000 + 10, inf = 1e9;

struct Node {
  int idx, val;
  Node(int a = 0, int b = 0) : idx(a), val(b) {}
  bool operator < (const Node &rhs) const {
    return val > rhs.val;
  }
};

struct Rec {
  int x1, y1, x2, y2;
  bool operator < (const Rec &rhs) const {
    return x1 < rhs.x1;
  }
  bool in(int x, int y) const {
    return x > x1 && x < x2 && y > y1 && y < y2;
  }
  void read() {
    scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
  }
};

struct Point {
  int x, y;
  Point(int a = 0, int b = 0) : x(a), y(b) {}
};

vector<Node> G[MAXN];
Point P[MAXN];
Rec R[MAXN];
int id[MAXN], dis[MAXN];
int n, N, ret;

bool ok(int x, int y) {
  for (int i = 0; i < n; ++ i) {
    if (R[i].in(x, y)) return false;
  }
  return true;
}

bool cmp(int a, int b) {
  return P[a].x < P[b].x;
}

void link(int u, int v, int w) {
  G[u].push_back(Node(v, w));
}

int dijkstra(int s, int t) {
  for (int i = 0; i < N * 2; ++ i) dis[i] = inf;
  priority_queue<Node> Q; Q.push(Node(s, 0)); dis[s] = 0;
  while (!Q.empty()) {
    Node now = Q.top(); Q.pop();
    if (now.val >= ret) return inf;
    if (now.idx == t) return now.val;
    if (now.val > dis[now.idx]) continue;
    for (auto &x : G[now.idx]) {
      Node nxt(x.idx, now.val + x.val);
      if (nxt.val < dis[x.idx]) {
        Q.push(nxt); dis[x.idx] = nxt.val;
      }
    }
  }
  return inf;
}

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++ i) R[i].read();
  int X = R[0].x1, Y = R[0].y1;
  sort(R, R + n); N = 0;
  for (int i = 0; i < n; ++ i) {
    if (ok(R[i].x1, R[i].y1)) P[N ++] = Point(R[i].x1, R[i].y1);
    if (ok(R[i].x1, R[i].y2)) P[N ++] = Point(R[i].x1, R[i].y2);
    if (ok(R[i].x2, R[i].y1)) P[N ++] = Point(R[i].x2, R[i].y1);
    if (ok(R[i].x2, R[i].y2)) P[N ++] = Point(R[i].x2, R[i].y2);
  }
  for (int i = 0; i < N; ++ i) id[i] = i;
  sort(id, id + N, cmp);
  for (int i = 0; i < N * 2; ++ i) G[i].clear();
  for (int i = 0; i < N; ++ i) {
    int u = id[i], j = 0;
    int mx = inf, mn = 0;
    for (; j < n && R[j].x1 < P[u].x; ++ j) {
      if (R[j].x2 > P[u].x) {
        if (P[u].y <= R[j].y1) mx = min(mx, R[j].y1);
        else mn = max(mn, R[j].y2);
      }
    }
    if (mx < mn) break;
    for (int k = i + 1; k < N; ++ k) {
      int v = id[k];
      for (; j < n && R[j].x1 < P[v].x; ++ j) {
        if (R[j].y1 < P[u].y && R[j].y2 > P[u].y) {
          mn = R[j].y2; mx = R[j].y1;
        }
        else if (R[j].y1 >= P[u].y) mx = min(mx, R[j].y1);
        else if (R[j].y2 <= P[u].y) mn = max(mn, R[j].y2);
      }
      if (mx < mn) break;
      if (P[v].y >= mn && P[v].y <= mx) {
        int w = abs(P[u].x - P[v].x) + abs(P[u].y - P[v].y);
        if (P[u].x <= X && P[v].x > X && P[u].y <= Y && P[v].y <= Y) {
          link(u, v + N, w); link(v, u + N, w);
          link(u + N, v, w); link(v + N, u, w);
        }
        else {
          link(u, v, w); link(u + N, v + N, w);
          link(v, u, w); link(v + N, u + N, w);
        }
      }
    }
  }
  ret = inf;
  for (int i = 0; i < N; ++ i) {
    ret = min(ret, dijkstra(i, i + N));
  }
  cout << ret << endl;
  return 0;
}

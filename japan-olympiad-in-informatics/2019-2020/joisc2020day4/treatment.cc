#include <cstdio>
#include <cassert>
#include <queue>
#include <algorithm>

const int inf = 2e9 + 10;
const int N = 1e5 + 10;

using int64 = long long;

struct Treatment {
  int l, r, t, c;
  bool operator < (const Treatment &rhs) const {
    return t < rhs.t;
  }
} ts[N];

struct Node {
  int m1, m2;
} T[N << 2];

void update(int o) {
  T[o].m1 = std::min(T[o << 1].m1, T[o << 1 | 1].m1);
  T[o].m2 = std::min(T[o << 1].m2, T[o << 1 | 1].m2);
}

void build(int o, int l, int r) {
  if (l + 1 == r) {
    T[o].m1 = ts[l].l + ts[l].t;
    T[o].m2 = ts[l].l - ts[l].t;
    return;
  }
  int m = (l + r) >> 1;
  build(o << 1, l, m);
  build(o << 1 | 1, m, r);
  update(o);
}

void del(int o, int l, int r, int x) {
  if (l + 1 == r) {
    T[o].m1 = T[o].m2 = inf;
    return;
  }
  int m = (l + r) >> 1;
  if (x < m) del(o << 1, l, m, x);
  else del(o << 1 | 1, m, r, x);
  update(o);
}

int query_suffix(int o, int l, int r, int bound, int v) { // [bound, inf)
  if (r <= bound || T[o].m1 > v) return -1;
  if (l + 1 == r) return l;
  int m = (l + r) >> 1, ret = -1;
  if (m < bound) ret = query_suffix(o << 1 | 1, m, r, bound, v);
  else if (bound <= m && T[o << 1 | 1].m1 <= v) ret = query_suffix(o << 1 | 1, m, r, bound, v);
  else ret = query_suffix(o << 1, l, m, bound, v);
  return ret;
}

int query_prefix(int o, int l, int r, int bound, int v) { // [0, bound)
  if (bound <= l || T[o].m2 > v) return -1;
  if (l + 1 == r) return l;
  int m = (l + r) >> 1, ret = -1;
  if (m > bound) ret = query_prefix(o << 1, l, m, bound, v);
  else if (m <= bound && T[o << 1].m2 <= v) ret = query_prefix(o << 1, l, m, bound, v);
  else ret = query_prefix(o << 1 | 1, m, r, bound, v);
  return ret;
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; ++i) {
    scanf("%d%d%d%d", &ts[i].t, &ts[i].l, &ts[i].r, &ts[i].c);
    --ts[i].l;
  }
  std::sort(ts, ts + m);
  build(1, 0, m);
  std::priority_queue<std::pair<int64, int>> pq;
  std::vector<int64> dist(m, -1);
  for (int i = 0; i < m; ++i) if (ts[i].l == 0) {
    dist[i] = ts[i].c;
    pq.emplace(-dist[i], i);
    del(1, 0, m, i);
  }
  int64 ret = -1;
  while (!pq.empty()) {
    int u = pq.top().second;
    pq.pop();
    if (ts[u].r == n) {
      ret = dist[u];
      break;
    }
    int left = 0, right = m - 1;
    while (left < right) {
      int mid = (left + right - 1) >> 1;
      if (ts[mid].t >= ts[u].t) right = mid;
      else left = mid + 1;
    }
    for ( ; ; ) {
      int v = query_suffix(1, 0, m, right, ts[u].r + ts[u].t);
      if (v == -1) break;
      assert(ts[v].l + ts[v].t <= ts[u].r + ts[u].t);
      dist[v] = dist[u] + ts[v].c;
      pq.emplace(-dist[v], v);
      del(1, 0, m, v);
    }
    left = 0, right = m - 1;
    while (left < right) {
      int mid = (left + right + 1) >> 1;
      if (ts[mid].t <= ts[u].t) left = mid;
      else right = mid - 1;
    }
    for ( ; ; ) {
      int v = query_prefix(1, 0, m, right + 1, ts[u].r - ts[u].t);
      if (v == -1) break;
      dist[v] = dist[u] + ts[v].c;
      pq.emplace(-dist[v], v);
      del(1, 0, m, v);
    }
  }
  printf("%lld\n", ret);
  return 0;
}

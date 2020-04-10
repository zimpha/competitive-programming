#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using int64 = long long;

const int N = 2e5 + 10;

int A[N], B[N], C[N];
int X[N], Z[N];
int64 Y[N];
int ret[N];

std::vector<int> queries[N];
std::vector<int> edges[N];

namespace centroid {
int root, mins, total;
int size[N], mark[N];
int visited[N], top[N];
int vid;

void get_center(int u, int p = -1) {
  int mx = 0; size[u] = 1;
  for (auto &e: edges[u]) {
    int v = A[e] + B[e] - u;
    if (v == p || mark[v]) continue;
    get_center(v, u);
    size[u] += size[v];
    mx = std::max(mx, size[v]);
  }
  mx = std::max(mx, total - size[u]);
  if (mx < mins) mins = mx, root = u;
}

int64 dist[N];
int st[N], ed[N], nodes[N], sz;
void dfs(int u, int p = -1) {
  if (u == root) top[u] = u;
  else top[u] = p == root ? u : top[p];
  nodes[sz] = u;
  st[u] = sz++;
  size[u] = 1;
  for (auto e: edges[u]) {
    int v = A[e] + B[e] - u;
    if (v == p || mark[v]) continue;
    visited[e] = vid;
    dist[v] = dist[u] + C[e];
    dfs(v, u);
    size[u] += size[v];
  }
  ed[u] = sz;
}

std::vector<std::pair<int, int>> add[N], sub[N];
void add_query(int l, int r, int q, int s) {//[l, r)
  add[l].emplace_back(q, s);
  sub[r].emplace_back(q, s);
}
std::vector<int64> xs;
int bit[N];
void solve() {
  xs.resize(sz);
  for (int i = 0; i < sz; ++i) xs[i] = dist[nodes[i]];
  std::sort(xs.begin(), xs.end());
  xs.erase(std::unique(xs.begin(), xs.end()), xs.end());
  int m = xs.size();
  for (int i = 0; i <= m; ++i) bit[i] = 0;
  for (int i = sz - 1; i >= 0; --i) {
    int x = std::lower_bound(xs.begin(), xs.end(), dist[nodes[i]]) - xs.begin();
    for (; x <= m; x += ~x & x + 1) bit[x] += 1;
    for (auto &e: add[i]) {
      int q = e.first, s = e.second;
      int64 bound = Y[q] - dist[X[q]];
      x = std::upper_bound(xs.begin(), xs.end(), bound) - xs.begin() - 1;
      for (; x >= 0; x -= ~x & x + 1) ret[q] += s * bit[x];
    }
    for (auto &e: sub[i]) {
      int q = e.first, s = e.second;
      int64 bound = Y[q] - dist[X[q]];
      x = std::upper_bound(xs.begin(), xs.end(), bound) - xs.begin() - 1;
      for (; x >= 0; x -= ~x & x + 1) ret[q] -= s * bit[x];
    }
  }
}

void work(int u, int tot) {
  total = tot; mins = tot * 2;
  get_center(u);
  mark[u = root] = true;
  sz = 0; vid++;
  dist[root] = 0;
  dfs(u);
  for (int i = 0; i <= sz; ++i) {
    add[i].clear();
    sub[i].clear();
  }
  for (int i = 0; i < sz; ++i) {
    for (auto &q: queries[nodes[i]]) {
      int x = X[q], z = Z[q];
      if (visited[z] != vid) {
        add_query(0, sz, q, 1);
        if (x != root) add_query(st[top[x]], ed[top[x]], q, -1);
      } else {
        int a = A[z], b = B[z];
        if (st[a] <= st[x] && ed[a] >= ed[x] && st[b] <= st[x] && ed[b] >= ed[x]) {
          continue;
        }
        add_query(0, sz, q, 1);
        if (x == root) {
          if (dist[a] > dist[b]) std::swap(a, b);
          add_query(st[b], ed[b], q, -1);
        } else {
          add_query(st[top[x]], ed[top[x]], q, -1);
          if (top[a] == top[x]) continue;
          if (dist[a] > dist[b]) std::swap(a, b);
          add_query(st[b], ed[b], q, -1);
        }
      }
    }
  }
  solve();
  for (auto &e: edges[u]) {
    int v = A[e] + B[e] - u;
    if (!mark[v]) work(v, size[v]);
  }
}
}

struct FastIO {
  static const int S = 655360;
  char buf[S];
  int pos, len;
  bool eof;
  FILE *in;
  FastIO(FILE *_in = stdin) {
    in = _in;
    pos = len = 0;
    eof = false;
  }
  inline int nextChar() {
    if (pos == len)
      pos = 0, len = fread(buf, 1, S, in);
    if (pos == len) {eof = true; return -1;}
    return buf[pos++];
  }
  inline int nextUInt() {
    int c = nextChar(), x = 0;
    while (c <= 32) c = nextChar();
    for (;'0' <= c && c <= '9'; c = nextChar()) x = x * 10 + c - '0';
    return x;
  }
  inline int64 nextU64() {
    int64 c = nextChar(), x = 0;
    while (c <= 32) c = nextChar();
    for (;'0' <= c && c <= '9'; c = nextChar()) x = x * 10 + c - '0';
    return x;
  }
  inline int nextInt() {
    int s = 1, c = nextChar(), x = 0;
    while (c <= 32) c = nextChar();
    if (c == '-') s = -1, c = nextChar();
    for (; '0' <= c && c <= '9'; c = nextChar()) x = x * 10 + c - '0';
    return x * s;
  }
  inline void nextString(char *s) {
    int c = nextChar();
    while (c <= 32) c = nextChar();
    for(; c > 32; c = nextChar()) *s++ = c;
    *s = 0;
  }
} io;

int main() {
  int n, m;
  n = io.nextUInt();
  for (int i = 0; i + 1 < n; ++i) {
    A[i] = io.nextUInt() - 1;
    B[i] = io.nextUInt() - 1;
    C[i] = io.nextUInt();
    edges[A[i]].push_back(i);
    edges[B[i]].push_back(i);
  }
  m = io.nextUInt();
  for (int i = 0; i < m; ++i) {
    X[i] = io.nextUInt() - 1;
    Y[i] = io.nextU64();
    Z[i] = io.nextUInt() - 1;
    queries[X[i]].push_back(i);
  }
  centroid::work(0, n);
  for (int i = 0; i < m; ++i) printf("%d\n", ret[i]);
  return 0;
}

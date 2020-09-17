#include <cstdio>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>

using int64 = long long;

const int N = 5e5 + 10, M = 2e6 + 10;
const int mod = 1e9 + 7;

struct Edge {
  int to, nx;
} edges[M * 3];

int64 pw[N];
int queue[N * 2];
int G[N], GR[N], SG[N];
int label[N], deg[N * 2];
int n, m, a, b;
int ne, nb, sz;

void add_edge(int* G, int u, int v) {
  edges[sz] = {v, G[u]};
  G[u] = sz++;
}

void relabel() {
  memset(label, -1, sizeof(*label) * n);
  int head = 0, tail = 0;
  for (int i = 0; i < a; ++i) {
    queue[tail++] = i;
    label[i] = i;
  }
  for (; head < tail; ++head) {
    int u = queue[head];
    for (int it = GR[u]; ~it; it = edges[it].nx) {
      int v = edges[it].to;
      if (label[v] == -1) {
        queue[tail++] = v;
        label[v] = v;
      }
    }
  }
  ne = nb = 0;
  for (int i = a; i < a + b; ++i) {
    if (label[i] == -1) ++ne;
    else label[i] = nb++;
  }
}

struct Tarjan {// index from 0 to n - 1
  int low[N], dfn[N], col[N];
  int stk[N], top, cnt, sz;
  void dfs(int x, int *G) {
    low[x] = dfn[x] = ++sz;
    stk[++top] = x;
    for (int it = G[x]; ~it; it = edges[it].nx) {
      int y = edges[it].to;
      if (!dfn[y]) {
        dfs(y, G);
        low[x] = std::min(low[x], low[y]);
      }
      else if (col[y] == -1) {
        low[x] = std::min(low[x], dfn[y]);
      }
    }
    if (dfn[x] == low[x]) {
      ++cnt;
      do {
        col[stk[top]] = cnt - 1;
      } while (stk[top--] != x);
    }
  }
  void run(int n, int *G) {
    sz = top = cnt = 0;
    memset(dfn,  0, sizeof(*dfn) * n);
    memset(col, -1, sizeof(*col) * n);
    for (int i = 0; i < n; ++i) {
      if (!dfn[i]) dfs(i,G);
    }
  }
} scc;

struct Bound {
  std::vector<std::pair<int, int>> iv;
  int L, R;
  void add(int l, int r) {
    if (l <= r) iv.emplace_back(l, r);
    else {
      iv.emplace_back(0, r);
      iv.emplace_back(l, nb - 1);
    }
  }
  void build() {
    L = R = -1;
    if (iv.empty()) return;
    std::sort(iv.begin(), iv.end());
    int l = iv[0].first, r = iv[0].second;
    for (auto &e: iv) {
      if (e.first <= r + 1) r = std::max(r, e.second);
      else {
        assert(L == -1 && l == 0);
        L = l, R = r;
        l = e.first;
        r = e.second;
      }
    }
    iv.clear();
    if (L == -1) L = l, R = r;
    else assert(r == nb - 1), L = l;
  }
} bound[N];

void get_bound() {
  scc.run(n, G);
  for (int i = a; i < a + b; ++i) if (label[i] != -1) {
    bound[scc.col[i]].add(label[i], label[i]);
  }
  memset(SG, -1, sizeof(*SG) * scc.cnt);
  memset(deg, 0, sizeof(*deg) * scc.cnt);
  for (int i = 0; i < n; ++i) {
    int u = scc.col[i];
    for (int it = G[i]; ~it; it = edges[it].nx) {
      int v = scc.col[edges[it].to];
      if (u != v) add_edge(SG, u, v), ++deg[v];
    }
  }
  int head = 0, tail = 0;
  for (int i = 0; i < scc.cnt; ++i) {
    if (deg[i] == 0) queue[tail++] = i;
  }
  for (; head < tail; ++head) {
    int u = queue[head];
    bound[u].build();
    int l = bound[u].L, r = bound[u].R;
    for (int it = SG[u]; ~it; it = edges[it].nx) {
      int v = edges[it].to;
      if (l != -1) bound[v].add(l, r);
      if (--deg[v] == 0) queue[tail++] = v;
    }
  }
}

int parent[N * 2];
int st[N], len[N], xs[N];
int f[N][3];

int get_root(int x) {
  return parent[x] == -1 ? x : parent[x] = get_root(parent[x]);
}

int solve() {
  // keep shortest interval whose left end is l
  memset(deg, -1, sizeof(*deg) * nb);
  for (int i = 0; i < a; ++i) {
    int idx = scc.col[i];
    int l = bound[idx].L, r = bound[idx].R;
    int len = 0;
    if (l == -1 || r == -1) return 0;
    if (l <= r) len = r - l + 1;
    else len = r + 1 + nb - l;
    if (deg[l] == -1 || deg[l] > len) deg[l] = len;
  }
  for (int i = 0; i < nb; ++i) deg[i + nb] = deg[i];
  // eliminate other useless interval
  memset(parent, -1, sizeof(*parent) * nb * 2);
  int top = 0;
  std::vector<bool> remove(nb * 2, false);
  for (int i = nb * 2 - 1; i >= 0; --i) {
    if (deg[i] == -1) deg[i] = mod, remove[i] = 1;
    else {
      int r = std::min(i + deg[i] - 1, nb * 2 - 1);
      auto idx = get_root(r);
      if (idx != i && deg[idx] != mod && idx + deg[idx] <= i + deg[i]) remove[i] = 1;
    }
    while (top && i + deg[i] <= queue[top - 1] + deg[queue[top - 1]]) {
      parent[queue[--top]] = i;
    }
    queue[top++] = i;
  }
  int best_i = -1, best_c = -1;
  for (int i = 0; i < nb; ++i) {
    if (!remove[i] && !remove[i + nb]) {
      if (best_c == -1 || deg[i] < best_c) {
        best_c = deg[i];
        best_i = i;
      }
    } else {
      deg[i] = -1;
    }
  }
  std::rotate(deg, deg + best_i, deg + nb);
  int n = 0, m = 0;
  xs[m++] = nb;
  assert(deg[0] != -1);
  for (int i = 0; i < nb; ++i) if (deg[i] != -1) {
    st[n] = i;
    len[n++] = deg[i];
    xs[m++] = i;
    xs[m++] = (i + deg[i]) % nb;
  }
  std::sort(xs, xs + m);
  m = std::unique(xs, xs + m) - xs;
  memset(label, -1, sizeof(*label) * nb);
  for (int i = 0; i < m; ++i) label[xs[i]] = i;
  int64 ret = 0;
  int *mx = deg;
  for (int z = 0; z < m; ++z) {
    if (xs[z + 1] <= len[0]) {
      int left = xs[z], right = xs[z + 1] - 1;
      for (int i = 0; i < m; ++i) mx[i] = m;
      for (int i = 0; i < n; ++i) {
        int l = st[i], r = (l + len[i] - 1) % nb;
        bool inc = false;
        if (l <= r) inc = l <= left && right <= r;
        else inc = l <= left || right <= r;
        if (!inc) {
          r = std::min(l + len[i], nb);
          if (l < right + 1) l = right + 1;
          assert(r - 1 >= l);
          mx[label[l]] = label[r];
        }
      }
      for (int i = m - 1; i >= 0; --i) {
        mx[i - 1] = std::min(mx[i - 1], mx[i]);
      }
      f[m][0] = f[m][1] = f[m][2] = 0;
      f[m - 1][0] = f[m - 1][1] = f[m - 1][2] = 1;
      for (int i = m - 2; i > z; --i) {
        static int64 g[3];
        g[0] = (f[i + 1][0] - f[mx[i]][0] + mod) % mod;
        g[1] = (f[i + 1][1] - f[m][1] + mod) % mod;
        g[2] = f[i + 1][2] * (pw[xs[i + 1] - xs[i]] - 2 + mod) % mod;
        f[i][0] = (f[i + 1][0] + g[1] + g[2]) % mod;
        f[i][1] = (f[i + 1][1] + g[0] + g[2]) % mod;
        f[i][2] = (g[0] + g[1] + g[2]) % mod;
      }
      ret += f[z + 1][2] * (pw[xs[z + 1] - xs[z]] - 1) % mod;
    } else break;
  }
  return ret % mod;
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
  n = io.nextUInt();
  m = io.nextUInt();
  a = io.nextUInt();
  b = io.nextUInt();
  pw[0] = 1;
  for (int i = 1; i <= n; ++i) {
    pw[i] = pw[i - 1] * 2 % mod;
  }
  sz = 0;
  memset(G, -1, sizeof(*G) * n);
  memset(GR, -1, sizeof(*GR) * n);
  for (int i = 0; i < m; ++i) {
    char c[10];
    int u = io.nextUInt() - 1;
    io.nextString(c);
    int v = io.nextUInt() - 1;
    if (c[1] == '>') {
      add_edge(G, v, u);
      add_edge(GR, u, v);
    } else {
      add_edge(G, u, v), add_edge(G, v, u);
      add_edge(GR, u, v), add_edge(GR, v, u);
    }
  }
  relabel();

  if (nb == 0) {
    puts("0");
    return 0;
  }

  get_bound();

  int ret = pw[ne] * solve() % mod;

  printf("%d\n", ret);
  return 0;
}

#include <ctime>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <random>
#include <algorithm>

using int64 = long long;
using uint64 = unsigned long long;

const int N = 25000 + 10, M = N * 18;
const int seed1 = 671141;
const uint64 mod1 = 1945555039024054273ull;
const int mod = 1e9 + 7;

struct Edge {
  int to, w, nx;
} edges[N * 2];

int G[N], sz;
uint64 p1[N], pw[N];
int xs[N], ns;
int n, m;

namespace path {
  struct Hash {
    uint64 h;
    Hash(uint64 h = 0): h(h) {}
    Hash operator + (const Hash &rhs) const {
      uint64 u = h + rhs.h;
      if (u >= mod1) u -= mod1;
      return {u};
    }
    Hash& operator += (const Hash &rhs) {
      h += rhs.h; if (h >= mod1) h -= mod1;
      return *this;
    }
    bool operator == (const Hash &rhs) const {
      return h == rhs.h;
    }
    void update(int x) {
      h += p1[xs[x]]; if (h >= mod1) h -= mod1;
    }
  };

  struct Node {
    int l, r;
    Hash hash;
    int cnt;
  } T[M * 16];
  int sz;
  
  void init() {
    T[0].l = T[0].r = 0;
    T[0].hash = Hash();
    T[0].cnt = 0;
    sz = 1;
  }
  int ins(int o, int l, int r, int x) {
    int p = sz++;
    T[p] = T[o];
    T[p].hash.update(x);
    T[p].cnt = T[p].cnt + 1;
    if (l + 1 == r) return p;
    int m = (l + r) >> 1;
    if (x < m) T[p].l = ins(T[p].l, l, m, x);
    else T[p].r = ins(T[p].r, m, r, x);
    return p;
  }
  int cmp(int a, int b, int l, int r) {
    if (T[a].hash == T[b].hash) return 0;
    while (l + 1 != r) {
      int m = (l + r) >> 1;
      int ra = T[a].r, rb = T[b].r;
      if (T[ra].hash == T[rb].hash) r = m, a = T[a].l, b = T[b].l;
      else l = m, a = ra, b = rb;
    }
    return T[a].cnt < T[b].cnt ? -1 : 1;
  }
  int cmp(int a, int b, int c, int d, int l, int r) {
    if (T[a].hash + T[b].hash == T[c].hash + T[d].hash) return 0;
    while (l + 1 != r) {
      int m = (l + r) >> 1;
      int ra = T[a].r, rb = T[b].r, rc = T[c].r, rd = T[d].r;
      if (T[ra].hash + T[rb].hash == T[rc].hash + T[rd].hash) r = m, a = T[a].l, b = T[b].l, c = T[c].l, d = T[d].l;
      else l = m, a = ra, b = rb, c = rc, d = rd;
    }
    return T[a].cnt + T[b].cnt < T[c].cnt + T[d].cnt ? -1 : 1;
  }
  int get_val(int a, int b, int l, int r) {
    if (l + 1 == r) return (T[a].cnt + T[b].cnt) * pw[xs[l]] % mod;
    int m = (l + r) >> 1, ret = 0;
    ret += get_val(T[a].l, T[b].l, l, m);
    ret += get_val(T[a].r, T[b].r, m, r);
    return ret % mod;
  }
}

int roots[M * 2], seq[M * 2], cnt[M * 2], offset;
int L[M], R[M];
std::vector<std::pair<int, int>> ivs[N];
std::pair<int, int> extra[M];

namespace centroid {
int size[N], mark[N];
int total, ms, root;

void init(int n) {
  offset = 0;
  memset(mark, 0, sizeof(*mark) * n);
}

void get_center(int u, int p = -1) {
  int mx = 0; size[u] = 1;
  for (int it = G[u]; ~it; it = edges[it].nx) {
    int v = edges[it].to;
    if (v == p || mark[v]) continue;
    get_center(v, u);
    size[u] += size[v];
    mx = std::max(mx, size[v]);
  }
  mx = std::max(mx, total - size[u]);
  if (mx < ms) ms = mx, root = u;
}

int l1, l2;
void dfs(int u, int o, int p = -1) {
  //printf("o=%d root=%d u=%d h=%d\n", o, root, u, path::T[o].hash.h);
  roots[l1++] = roots[l2++] = o;
  for (int it = G[u]; ~it; it = edges[it].nx) {
    int v = edges[it].to;
    if (v == p || mark[v]) continue;
    dfs(v, path::ins(o, 0, ns, edges[it].w), u);
  }
}

void work(int u, int tot) {
  if (tot == 1) return;
  total = tot, ms = tot * 2, root = u;
  get_center(u);
  mark[u = root] = true;
  get_center(u);
  ivs[u].emplace_back(offset, offset + size[u]);
  l1 = offset; offset += size[u];
  roots[l1++] = 0;
  for (int it = G[u]; ~it; it = edges[it].nx) {
    int v = edges[it].to;
    if (mark[v]) continue;
    ivs[u].emplace_back(offset, offset + size[v]);
    l2 = offset; offset += size[v];
    dfs(v, path::ins(0, 0, ns, edges[it].w));
  }
  for (int it = G[u]; ~it; it = edges[it].nx) {
    int v = edges[it].to;
    if (!mark[v]) work(v, size[v]);
  }
}
}

bool cmp_roots(int a, int b) {
  return path::cmp(a, b, 0, ns) < 0;
}

int cmp(int a, int b, int c, int d) {
  return path::cmp(a, b, c, d, 0, ns);
}

template<int sign>
void count(int &less, int &equal, int x, int y, int l, int r) {
  for (int i = l, j = r - 1, re; i <= j; ++i) {
    int ci = i == l ? cnt[i] : cnt[i] - cnt[i - 1];
    while (j >= i && (re = cmp(roots[i], roots[j], x, y)) > 0) --j;
    if (j < i) break;
    int cj = j == l ? cnt[j] : cnt[j] - cnt[j - 1];
    if (re == 0) {
      if (i == j) equal += ci * (ci - 1) / 2 * sign;
      else equal += ci * cj * sign;
      if (i < j) {
        less += ci * (ci - 1) / 2 * sign;
        less += ci * (cnt[j - 1] - cnt[i]) * sign; 
      }
    } else {
      less += ci * (ci - 1) / 2 * sign;
      less += ci * (cnt[j] - cnt[i]) * sign; 
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
  p1[0] = pw[0] = 1;
  for (int i = 1; i <= n; ++i) {
    p1[i] = p1[i - 1] * seed1 % mod1;
    pw[i] = pw[i - 1] * n % mod;
  }
  sz = 0;
  memset(G, -1, sizeof(*G) * n);
  ns = 0; xs[ns++] = 0;
  for (int i = 1; i < n; ++i) {
    int u = io.nextUInt() - 1;
    int v = io.nextUInt() - 1;
    int w = io.nextUInt();;
    edges[sz] = (Edge){v, w, G[u]}; G[u] = sz++;
    edges[sz] = (Edge){u, w, G[v]}; G[v] = sz++;
    xs[ns++] = w;
  }
  std::sort(xs, xs + ns);
  ns = std::unique(xs, xs + ns) - xs;
  for (int i = 0; i < sz; ++i) {
    edges[i].w = std::lower_bound(xs, xs + ns, edges[i].w) - xs;
  }
  path::init();
  centroid::init(n);
  centroid::work(0, n);
  sz = 0; seq[sz++] = 0;
  for (int i = 0; i < n; ++i) if (!ivs[i].empty()) {
    for (auto &e: ivs[i]) {
      std::sort(roots + e.first, roots + e.second, cmp_roots);
    }
    assert(roots[ivs[i][0].first] == 0);
    for (int j = ivs[i][0].first + 1; j < ivs[i][0].second; ++j) {
      seq[sz++] = roots[j];
    }
    for (auto &e: ivs[i]) {
      int m = e.first; cnt[m] = 1;
      for (int j = e.first + 1; j < e.second; ++j) {
        if (path::cmp(roots[j], roots[m], 0, ns) == 0) ++cnt[m];
        else roots[++m] = roots[j], cnt[m] = cnt[m - 1] + 1;
      }
      e.second = m + 1;
    }
  }
  std::sort(seq, seq + sz, cmp_roots);
  for (int i = 0; i < sz; ++i) {
    L[i] = i + 1;
    R[i] = sz;
  }
  std::mt19937_64 gen{time(NULL)};
  while (true) {
    int64 sum = 0;
    for (int i = 0; i < sz; ++i) {
      if (L[i] < R[i]) sum += R[i] - L[i];
    }
    auto rank = std::uniform_int_distribution<int64>(0, sum - 1)(gen);
    int x = -1, y = -1;
    for (int i = 0; i < sz; ++i) if (L[i] < R[i]) {
      if (rank >= R[i] - L[i]) rank -= R[i] - L[i];
      else {
        x = i, y = L[i] + rank;
        break;
      }
    }
    if (sum <= 200000) break;
    int less = 0, equal = 0;
    for (int i = 0; i < n; ++i) if (!ivs[i].empty()) {
      count<1>(less, equal, seq[x], seq[y], ivs[i][0].first, ivs[i][0].second);
      for (size_t j = 1; j < ivs[i].size(); ++j) {
        count<-1>(less, equal, seq[x], seq[y], ivs[i][j].first, ivs[i][j].second);
      }
    }
    if (less < m && less + equal >= m) {
      printf("%d\n", path::get_val(seq[x], seq[y], 0, ns));
      return 0;
    }
    if (less + equal < m) { // remove <= a[x] + a[y]
      for (int i = 0, j = sz - 1; i < sz; ++i) {
        while (i < j && cmp(seq[i], seq[j], seq[x], seq[y]) > 0) --j;
        L[i] = std::max(L[i], j + 1);
      }
    } else { // remove >= a[x] + a[y];
      for (int i = 0, j = sz - 1; i < sz; ++i) {
        while (i < j && cmp(seq[i], seq[j], seq[x], seq[y]) >= 0) --j;
        R[i] = std::min(R[i], j + 1);
      }
    }
  }
  int left = 0, right = 0;
  for (int i = 0; i < sz; ++i) {
    for (int j = L[i]; j < R[i]; ++j) {
      extra[right++] = {seq[i], seq[j]};
    }
  }
  std::sort(extra, extra + right, [&](const std::pair<int, int> &x, const std::pair<int, int> &y) {
    return cmp(x.first, x.second, y.first, y.second) < 0;
  });
  while (left < right) {
    int mid = (left + right) >> 1;
    int less = 0, equal = 0;
    int x = extra[mid].first, y = extra[mid].second;
    for (int i = 0; i < n; ++i) if (!ivs[i].empty()) {
      count<1>(less, equal, x, y, ivs[i][0].first, ivs[i][0].second);
      for (size_t j = 1; j < ivs[i].size(); ++j) {
        count<-1>(less, equal, x, y, ivs[i][j].first, ivs[i][j].second);
      }
    }
    if (less < m && less + equal >= m) {
      printf("%d\n", path::get_val(x, y, 0, ns));
      return 0;
    }
    if (less + equal < m) left = mid + 1;
    else right = mid - 1;
  }
  printf("%d\n", path::get_val(extra[left].first, extra[left].second, 0, ns));
  return 0;
}

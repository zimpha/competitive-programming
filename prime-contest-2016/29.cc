#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>

struct FastIO {
  static const int S = 1310720;
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

using ll = long long;

const int N = 1000000 + 10;

struct edges_t {
  int head[N], nxt[N], to[N], sz;
  void add(int x, int y) {
    to[++sz] = y;
    nxt[sz] = head[x];
    head[x] = sz;
  }
} queries, graph, edges;

int mark[N], fail[N], extend[N];
char s[N], t[N];
int n, m;

void kmp(int n, char *s, int fail[N]) {
  fail[0] = -1;
  for (int i = 1, j = -1; i < n; ++i) {
    while (j >= 0 && s[j + 1] != s[i]) j = fail[j];
    fail[i] = s[j + 1] == s[i] ? ++j : j;
  }
}

int st[N], ed[N], top;
void dfs1(int u) {
  st[u] = top++;
  for (int it = edges.head[u]; it; it = edges.nxt[it]) {
    dfs1(edges.to[it]);
  }
  ed[u] = top;
}

int u[N];
void add(int x, int v) {
  for (; x <= m; x += ~x & x + 1) u[x] += v;
}
int get(int x, int r = 0) {
  for (; x >= 0; x -= ~x & x + 1) r += u[x];
  return r;
}

ll dfs2(int u) {
  add(st[m - u], +1);
  add(ed[m - u], -1);
  ll ret = 0;
  for (int it = queries.head[u]; it; it = queries.nxt[it]) {
    ret += get(st[queries.to[it]]);
  }
  for (int it = graph.head[u]; it; it = graph.nxt[it]) {
    ret += dfs2(graph.to[it]);
  }
  add(st[m - u], -1);
  add(ed[m - u], +1);
  return ret;
}

int main() {
  io.nextString(s);
  io.nextString(t);
  m = io.nextUInt();
  for (int i = 0, p; i < m; ++i) {
    p = io.nextUInt();
    mark[p - 1] = true;
  }
  n = strlen(s);
  m = strlen(t);
  std::reverse(s, s + n);
  std::reverse(t, t + m);
  kmp(m, t, fail);
  memset(extend, -1, sizeof(extend));
  ll ret = 0;
  for (int i = 0, j = -1; i < n; ++i) {
    while (j >= 0 && t[j + 1] != s[i]) j = fail[j];
    if (t[j + 1] == s[i]) ++j;
    extend[n - i - 1] = j;
    if (j == m - 1) j = fail[j], ++ret;
  }
  for (int i = 0; i < m; ++i) {
    graph.add(fail[i] + 1, i + 1);
  }
  std::reverse(s, s + n);
  std::reverse(t, t + m);
  kmp(m, t, fail);
  for (int i = 0; i < m; ++i) {
    edges.add(fail[i] + 1, i + 1);
  }
  top = 0;
  dfs1(0);
  for (int i = 0, j = -1; i < n; ++i) {
    if (mark[i]) {
      queries.add(extend[i + 1] + 1, j + 1);
      ret -= extend[i + 1] == m - 1;
    } else {
      while (j >= 0 && t[j + 1] != s[i]) j = fail[j];
      if (t[j + 1] == s[i]) ++j;
      if (j == m - 1) j = fail[j];
    }
  }
  printf("%lld\n", dfs2(0) + ret);
  return 0;
}

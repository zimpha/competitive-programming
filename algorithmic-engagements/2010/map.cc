#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using pii = std::pair<int, int>;

const int N = 1000000 + 10;
int f[N], g[N], n, tot;
int xs[N], u[N], m;
pii P[N];

void ins(int x) {
  g[x] ++;
  for (; x <= m; x += ~x & x + 1) u[x] ++;
}
int get(int x) {
  int r = 0;
  for (; x >= 0; x -= ~x & x + 1) r += u[x];
  return r;
}

void solve() {
  for (int i = 0; i <= m; ++ i) u[i] = g[i] = 0; tot = 0;
  for (int i = 0, j; i < n; i = j) {
    int x = P[i].first;
    for (j = i; j < n && x == P[j].first; ++ j) {
      int cnt = get(P[j].second - 1);
      f[j] += (cnt > 0) + (tot > cnt + g[P[j].second]);
    }
    for (; i < j; ++ i) ins(P[i].second), ++tot;
  }
  for (int i = 0; i <= m; ++ i) u[i] = g[i] = 0; tot = 0;
  for (int i = n - 1, j; i >= 0; i = j) {
    int x = P[i].first;
    for (j = i; j >= 0 && x == P[j].first; -- j) {
      int cnt = get(P[j].second - 1);
      f[j] += (cnt > 0) + (tot > cnt + g[P[j].second]);
    }
    for (; i > j; -- i) ins(P[i].second), ++tot;
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
  for (int i = 0; i < n; ++ i) {
    P[i].first = io.nextUInt();
    P[i].second = io.nextUInt();
    xs[i] = P[i].second;
  }
  std::sort(P, P + n);
  std::sort(xs, xs + n);
  m = std::unique(xs, xs + n) - xs;
  for (int i = 0; i < n; ++ i) {
    P[i].second = std::lower_bound(xs, xs + m, P[i].second) - xs;
  }
  solve();
  int ret = 0;
  for (int i = 0; i < n; ++ i) {
    ret += f[i] == 4;
  }
  printf("%d\n", ret);
  return 0;
}

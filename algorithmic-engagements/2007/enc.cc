#include <cstdio>
#include <vector>
#include <algorithm>


struct FastIO {
  static const int S = 65536;
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
  int n = io.nextUInt();
  std::vector<int> bit1(n * 2), bit2(n * 2);
  long long ret1 = 0, ret2 = 0;
  int u = 0, v = 1, s = 1, t = 0;
  for (int i = 0, a, b; i < n * 2; ++i) {
    a = io.nextUInt();
    if (a == 0) a = v, v += 2, b = t, t += 2;
    else a = u, u += 2, b = s, s += 2;
    for (int x = a; x < 2 * n; x += ~x & x + 1) ret1 += bit1[x];
    for (int x = a; x >= 0; x -= ~x & x + 1) bit1[x] += 1;
    for (int x = b; x < 2 * n; x += ~x & x + 1) ret2 += bit2[x];
    for (int x = b; x >= 0; x -= ~x & x + 1) bit2[x] += 1;
  }
  printf("%lld\n", std::min(ret1, ret2));
  return 0;
}

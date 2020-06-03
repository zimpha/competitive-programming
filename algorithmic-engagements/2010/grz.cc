#include <cstdio>
#include <vector>
#include <algorithm>

using int64 = long long;

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
  int t = io.nextUInt();
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    a[i] = io.nextUInt();
  }
  int64 ret = 0;
  if (n == 1) ret = (int64)a[0] * (t / 2 + 1);
  else {
    int64 sum = 0;
    for (int i = 0; i < n; ++i) {
      sum += a[i];
      if (!i) continue;
      int u = t - i;
      if (u < 0) break;
      if (u & 1) ret = std::max(ret, sum + (int64)a[i - 1] * (u - u / 2) + (int64)a[i] * (u / 2));
      else ret = std::max(ret, sum + (int64)(a[i] + a[i - 1]) * (u / 2));
    }
  }
  printf("%lld\n", ret);
  return 0;
}

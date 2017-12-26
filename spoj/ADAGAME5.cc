#include <cstdio>
#include <cstring>
#include <cassert>
#include <set>

inline int palace(int x, int y) {
  constexpr int s[3][3] = {{0, 1, 2}, {1, 2, 0}, {2, 0, 1}};
  return s[x % 3][y % 3] + ((x / 3) ^ (y / 3)) * 3;
}

struct FastIO {
  static const int S = 65536 * 2;
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
  int T = io.nextUInt();
  for (int cas = 1; cas <= T; ++cas) {
    int n = io.nextUInt(), ret = 0;
    for (int i = 0; i < n; ++i) {
      int x = io.nextUInt();
      int y = io.nextUInt();
      ret ^= palace(x, y);
    }
    if (ret) puts("Ada");
    else puts("Vinit");
  }
  return 0;
}

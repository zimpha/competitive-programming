#include <cstdio>
#include <vector>
#include <algorithm>

const int N = 1e6 + 10, M = 100;

std::pair<int, int> sticks[N];
int candidate[M];

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
  int n, nn = 0;
  n = io.nextUInt();
  for (int i = 0; i < n; ++i) {
    int m = io.nextUInt();
    for (int j = 0, x; j < m; ++j) {
      sticks[nn].first = io.nextUInt();
      sticks[nn++].second = i;
    }
  }
  for (int i = 0; i < n; ++i) candidate[i] = -1;
  std::sort(sticks, sticks + nn);
  for (int i = 0; i < nn; ++i) {
    int a = sticks[i].first, ca = sticks[i].second;
    int b = 0, cb = -1;
    int c = 0, cc = -1;
    for (int j = 0; j < n; ++j) if (candidate[j] != -1 && ca != j) {
      int v = candidate[j];
      if (v >= b) c = b, cc = cb, b = v, cb = j;
      else if (v > c) c = v, cc = j;
    }
    if (b != 0 && c != 0 && b + c > a) {
      printf("%d %d %d %d %d %d\n", ca + 1, a, cb + 1, b, cc + 1, c);
      return 0;
    }
    candidate[sticks[i].second] = sticks[i].first;
  }
  puts("NIE");
  return 0;
}

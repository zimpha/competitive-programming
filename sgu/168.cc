#include <cstdio>
#include <algorithm>

const int N = 1000;

int A[N][N], B[N][N];

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
  int n = io.nextUInt(), m = io.nextUInt();
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      B[i][j] = A[i][j] = io.nextInt();
    }
  }
  for (int i = n - 1; i >= 0; --i) {
    for (int j = m - 1; j >= 0; --j) {
      if (j < m - 1) B[i][j] = std::min(B[i][j], B[i][j + 1]);
      if (i < n - 1) B[i][j] = std::min(B[i][j], B[i + 1][j]);
      if (j < m - 1) A[i][j] = std::min(A[i][j], A[i][j + 1]);
    }
  }
  for (int i = 1; i < n; ++i) {
    for (int j = 0; j + 1 < m; ++j) {
      A[i][j] = std::min(A[i][j], A[i - 1][j + 1]);
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (j) putchar(' ');
      printf("%d", std::min(A[i][j], B[i][j]));
    }
    puts("");
  }
  return 0;
}

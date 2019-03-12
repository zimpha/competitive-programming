#include <cstdio>
#include <cassert>
#include <cstring>
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
  void putchar(char c) {
    buf[pos++] = c;
    if (pos == S) fwrite(buf, 1, S, stdout), pos = 0;
  }
  void putInt(int x) {
    static char s[10];
    int m = 0;
    do {
      s[m++] = x % 10;
      x /= 10;
    } while (x);
    for (int i = m - 1; i >= 0; --i) putchar(s[i] + '0');
    putchar('\n');
  }
  void flush() {
    fwrite(buf, 1, pos, stdout), pos = 0;
  }
} io;

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    char c;
    scanf(" %c", &c);
    if (c == 'c') a[i] = 0;
    else if (c == 'n') a[i] = 1;
    else a[i] = 2;
  }
  auto b = a;
  std::sort(b.begin(), b.end());
  for (int i = 0; i < n; ++i) if (a[i] != b[i]) {
    int p = i;
    for (; p < n && a[p] != b[i]; ++p);
    if (p - i >= 3) {
      std::rotate(a.begin() + i, a.begin() + i + (p - i) / 3 * 3, a.end());
    }
    int e = (p - i) % 3, r = (n - i) % 3;
    if (r == 0) r = 3;
    int k = (n - i - r - 3) / 3;
    for (int j = i; j + 3 <= p; j += 3) io.putInt(i + 1);
    if (e == 0) continue;
    else if (e == 1) {
      if (r == 1) {
        std::rotate(a.begin() + i, a.begin() + i + 1, a.end());
        for (int j = 0; j < k * 2 + 3; ++j) io.putInt(i + 1);
      } else if (r == 2) {
        std::rotate(a.begin() + i, a.begin() + i + 1, a.end());
        for (int j = 0; j < k + 2; ++j) io.putInt(i + 1);
      } else if (r == 3) {
        std::rotate(a.begin() + i, a.begin() + i + 1, a.begin() + i + 4);
        io.putInt(i + 2);
        for (int j = 0; j < k + 1; ++j) io.putInt(i + 1);
      }
    } else {
      if (r == 1) {
        std::rotate(a.begin() + i, a.begin() + i + 2, a.end());
        for (int j = 0; j < k + 2; ++j) io.putInt(i + 1);
      } else if (r == 2) {
        std::rotate(a.begin() + i, a.begin() + i + 1, a.begin() + i + 4);
        std::rotate(a.begin() + i, a.begin() + i + 1, a.end());
        io.putInt(i + 2);
        for (int j = 0; j < k + 1; ++j) io.putInt(i + 1);
      } else if (r == 3) {
        std::rotate(a.begin() + i, a.begin() + i + 2, a.begin() + i + 5);
        io.putInt(i + 3);
        for (int j = 0; j < k + 1; ++j) io.putInt(i + 1);
      }
    }
  }
  io.flush();
  return 0;
}

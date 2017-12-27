#include <cstdio>
#include <cstring>
#include <algorithm>

struct FastIO {
  static const int S = 65536 * 4;
  char buf[S];
  int pos, len;
  bool eof;
  FILE *in;
  FastIO(FILE *_in = stdin) {
    in = _in;
    pos = len = 0;
    eof = false;
  }
  int nextChar() {
    if (pos == len)
      pos = 0, len = fread(buf, 1, S, in);
    if (pos == len) {eof = true; return -1;}
    return buf[pos++];
  }
  int nextUInt() {
    int c = nextChar(), x = 0;
    while (c <= 32) c = nextChar();
    for (;'0' <= c && c <= '9'; c = nextChar()) x = x * 10 + c - '0';
    return x;
  }
  int nextInt() {
    int s = 1, c = nextChar(), x = 0;
    while (c <= 32) c = nextChar();
    if (c == '-') s = -1, c = nextChar();
    for (; '0' <= c && c <= '9'; c = nextChar()) x = x * 10 + c - '0';
    return x * s;
  }
  void nextString(char *s) {
    int c = nextChar();
    while (c <= 32) c = nextChar();
    for(; c > 32; c = nextChar()) *s++ = c;
    *s = 0;
  }
} io;

const int N = 1000 + 10;

int A[N][N], n, m, k;
int up[N], row[N];

int subrec(int lim) {
  static int l[N], r[N];
  memset(up, 0, sizeof(*up) * m);
  int ret = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      row[j] = A[i][j] >= lim;
      if (row[j]) up[j]++;
      else up[j] = 0;
    }
    for (int j = 0; j < m; ++j) {
      for (l[j] = j; l[j] && up[j] <= up[l[j] - 1]; l[j] = l[l[j] - 1]);
    }
    for (int j = m - 1; j >= 0; --j) {
      for (r[j] = j; r[j] + 1 < m && up[j] <= up[r[j] + 1]; r[j] = r[r[j] + 1]);
      if (up[j]) ret = std::max(ret, up[j] * (r[j] - l[j] + 1));
    }
  }
  return ret;
}

int main() {
  int T = io.nextUInt();
  for (int cas = 1; cas <= T; ++cas) {
    n = io.nextUInt();
    m = io.nextUInt();
    k = io.nextUInt();
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        A[i][j] = io.nextUInt();
      }
    }
    int left = 0, right = 1e9, area = 0;
    while (left < right) {
      int mid = (left + right + 1) >> 1;
      int now = subrec(mid);
      if (now >= k) left = mid, area = now;
      else right = mid - 1;
    }
    printf("%d %d\n", left, area);
  }
  return 0;
}

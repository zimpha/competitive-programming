#include <cstdio>
#include <cassert>
#include <algorithm>

const int N = 1501;

int s[2][N][N], t[2][N][N];
int a[N][N], ret[N][N];

struct FastIO {
  static const int S = 65536;
  char buf[S], wbuf[S];
  int wl;
  int pos, len;
  bool eof;
  FILE *in, *out;
  FastIO(FILE *_in = stdin, FILE *_out = stdout) {
    in = _in;
    out = _out;
    pos = len = 0;
    wl = 0;
    eof = false;
  }
  ~FastIO() {
    flush();
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
  void flush() {
    if (wl) {
      fwrite(wbuf, 1, wl, stdout);
      wl = 0;
    }
  }
  void wchar(char c) {
    if (wl == S) flush();
    wbuf[wl++] = c;
  }
  void wuint(unsigned int x) {
    static char s[20];
    int m = 0;
    do {
      s[m++] = x % 10 + '0';
      x /= 10;
    } while (x);
    for (int i = m - 1; i >= 0; --i) {
      wchar(s[i]);
    }
  }
} io;

int main() {
  int n = io.nextUInt(), m = io.nextUInt();
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      a[i][j] = io.nextUInt();
      ret[i][j] = a[i][j];
      s[1][i][j] = 0;
    }
  }
  ++m;
  {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        s[0][i][j] = t[0][i][j] = a[i][j];
      }
    }
    int d = 1, u = 0, v = 1;
    while (d * 2 <= m) {
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
          s[v][i][j] = s[u][i][j];
          if (i >= d) s[v][i][j] = std::max(s[v][i][j], s[u][i - d][j]);
          if (j >= d) s[v][i][j] = std::max(s[v][i][j], s[u][i][j - d]);
          if (i >= d && j >= d) s[v][i][j] = std::max(s[v][i][j], s[u][i - d][j - d]);
          t[v][i][j] = s[u][i][j];
          if (i >= d) t[v][i][j] = std::max(t[v][i][j], t[u][i - d][j]);
          if (j >= d) t[v][i][j] = std::max(t[v][i][j], t[u][i][j - d]);
        }
      }
      std::swap(u, v);
      d *= 2;
    }
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (m - d) {
          int x = i - m + d / 2 * 3, y = j - m + d / 2 * 3;
          ret[i][j] = std::max(ret[i][j], s[v][i][j]);
          if (0 <= x && x < n) ret[i][j] = std::max(ret[i][j], s[v][x][j]);
          if (0 <= y && y < n) ret[i][j] = std::max(ret[i][j], s[v][i][y]);
          if (0 <= x && x < n && 0 <= y && y < n) ret[i][j] = std::max(ret[i][j], s[v][x][y]);
        }
        if (i - m + d >= 0) ret[i][j] = std::max(ret[i][j], t[u][i - m + d][j]);
        if (j - m + d >= 0) ret[i][j] = std::max(ret[i][j], t[u][i][j - m + d]);
      }
    }
  }
  {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        s[0][i][j] = t[0][i][j] = a[i][j];
      }
    }
    int d = 1, u = 0, v = 1;
    while (d * 2 <= m) {
      for (int i = 0; i < n; ++i) {
        for (int j = n - 1; j >= 0; --j) {
          s[v][i][j] = s[u][i][j];
          if (i >= d) s[v][i][j] = std::max(s[v][i][j], s[u][i - d][j]);
          if (j + d < n) s[v][i][j] = std::max(s[v][i][j], s[u][i][j + d]);
          if (i >= d && j + d < n) s[v][i][j] = std::max(s[v][i][j], s[u][i - d][j + d]);
          t[v][i][j] = s[u][i][j];
          if (i >= d) t[v][i][j] = std::max(t[v][i][j], t[u][i - d][j]);
          if (j + d < n) t[v][i][j] = std::max(t[v][i][j], t[u][i][j + d]);
        }
      }
      std::swap(u, v);
      d *= 2;
    }
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        assert(m >= d);
        if (m - d) {
          int x = i - m + d / 2 * 3, y = j + m - d / 2 * 3;
          ret[i][j] = std::max(ret[i][j], s[v][i][j]);
          if (0 <= x && x < n) ret[i][j] = std::max(ret[i][j], s[v][x][j]);
          if (0 <= y && y < n) ret[i][j] = std::max(ret[i][j], s[v][i][y]);
          if (0 <= x && x < n && 0 <= y && y < n) ret[i][j] = std::max(ret[i][j], s[v][x][y]);
        }
        if (i - m + d >= 0) ret[i][j] = std::max(ret[i][j], t[u][i - m + d][j]);
        if (j + m - d < n) ret[i][j] = std::max(ret[i][j], t[u][i][j + m - d]);
      }
    }
  }
  {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        s[0][i][j] = t[0][i][j] = a[i][j];
      }
    }
    int d = 1, u = 0, v = 1;
    while (d * 2 <= m) {
      for (int i = n - 1; i >= 0; --i) {
        for (int j = n - 1; j >= 0; --j) {
          s[v][i][j] = s[u][i][j];
          if (i + d < n) s[v][i][j] = std::max(s[v][i][j], s[u][i + d][j]);
          if (j + d < n) s[v][i][j] = std::max(s[v][i][j], s[u][i][j + d]);
          if (i + d < n && j + d < n) s[v][i][j] = std::max(s[v][i][j], s[u][i + d][j + d]);
          t[v][i][j] = s[u][i][j];
          if (i + d < n) t[v][i][j] = std::max(t[v][i][j], t[u][i + d][j]);
          if (j + d < n) t[v][i][j] = std::max(t[v][i][j], t[u][i][j + d]);
        }
      }
      std::swap(u, v);
      d *= 2;
    }
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (m - d) {
          int x = i + m - d / 2 * 3, y = j + m - d / 2 * 3;
          ret[i][j] = std::max(ret[i][j], s[v][i][j]);
          if (0 <= x && x < n) ret[i][j] = std::max(ret[i][j], s[v][x][j]);
          if (0 <= y && y < n) ret[i][j] = std::max(ret[i][j], s[v][i][y]);
          if (0 <= x && x < n && 0 <= y && y < n) ret[i][j] = std::max(ret[i][j], s[v][x][y]);
        }
        if (i + m - d < n) ret[i][j] = std::max(ret[i][j], t[u][i + m - d][j]);
        if (j + m - d < n) ret[i][j] = std::max(ret[i][j], t[u][i][j + m - d]);
      }
    }
  }
  {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        s[0][i][j] = t[0][i][j] = a[i][j];
      }
    }
    int d = 1, u = 0, v = 1;
    while (d * 2 <= m) {
      for (int i = n - 1; i >= 0; --i) {
        for (int j = 0; j < n; ++j) {
          s[v][i][j] = s[u][i][j];
          if (i + d < n) s[v][i][j] = std::max(s[v][i][j], s[u][i + d][j]);
          if (j >= d) s[v][i][j] = std::max(s[v][i][j], s[u][i][j - d]);
          if (i + d < n && j >= d) s[v][i][j] = std::max(s[v][i][j], s[u][i + d][j - d]);
          t[v][i][j] = s[u][i][j];
          if (i + d < n) t[v][i][j] = std::max(t[v][i][j], t[u][i + d][j]);
          if (j >= d) t[v][i][j] = std::max(t[v][i][j], t[u][i][j - d]);
        }
      }
      std::swap(u, v);
      d *= 2;
    }
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (m - d) {
          int x = i + m - d / 2 * 3, y = j - m + d / 2 * 3;
          ret[i][j] = std::max(ret[i][j], s[v][i][j]);
          if (0 <= x && x < n) ret[i][j] = std::max(ret[i][j], s[v][x][j]);
          if (0 <= y && y < n) ret[i][j] = std::max(ret[i][j], s[v][i][y]);
          if (0 <= x && x < n && 0 <= y && y < n) ret[i][j] = std::max(ret[i][j], s[v][x][y]);
        }
        if (i + m - d < n) ret[i][j] = std::max(ret[i][j], t[u][i + m - d][j]);
        if (j - m + d >= 0) ret[i][j] = std::max(ret[i][j], t[u][i][j - m + d]);
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (j) io.wchar(' ');
      io.wuint(ret[i][j]);
    }
    io.wchar('\n');
  }
  return 0;
}

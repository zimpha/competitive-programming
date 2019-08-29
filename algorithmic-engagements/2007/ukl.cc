#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>
#include <algorithm>

const int N = 50, M = 1600;

int dp[2][N][M];
int ways[N][N];
int go[M][M];
bool r[N][N];

struct Edge {
  int u, v, w;
  bool operator < (const Edge &rhs) const {
    return w < rhs.w;
  }
};

inline void update(int &x, int y, int mod) {
  if (x == -1) return;
  x += y;
  if (x >= mod) x -= mod;
}

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
  int m = io.nextUInt();
  int I = io.nextUInt();
  int mod = io.nextUInt();
  std::vector<int> dvs;
  for (int d = 1; d * d <= I; ++d) if (I % d == 0) {
    dvs.push_back(d);
    if (d * d != I) dvs.push_back(I / d);
  }
  int p = 0, s = I;
  for (int i = 2; i * i <= s; ++i) {
    while (s % i == 0) ++p, s /= i;
  }
  if (s > 1) ++p;
  std::sort(dvs.begin(), dvs.end());
  std::vector<Edge> edges(m);
  for (int i = 0; i < m; ++i) {
    edges[i].u = io.nextUInt() - 1;
    edges[i].v = io.nextUInt() - 1;
    edges[i].w = io.nextUInt();
    if (I % edges[i].w == 0) {
      edges[i].w = std::lower_bound(dvs.begin(), dvs.end(), edges[i].w) - dvs.begin();
    } else {
      edges[i].w = -1;
    }
    if (edges[i].w == 0) {
      r[edges[i].u][edges[i].v] = 1;
    }
  }
  for (int k = 0; k < n; ++k) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (i != k && k != j) {
          r[i][j] |= r[i][k] & r[k][j];
        }
      }
    }
  }
  std::sort(edges.begin(), edges.end());
  s = dvs.size();
  for (int i = 0; i < s; ++i) {
    go[i][0] = go[0][i] = i;
    for (int j = 1, z = i; j <= i; ++j) {
      while (z < s && dvs[i] * dvs[j] > dvs[z]) ++z;
      if (z < s && dvs[i] * dvs[j] == dvs[z]) go[i][j] = z;
      else go[i][j] = -1;
      go[j][i] = go[i][j];
    }
  }
  memset(ways, 0, sizeof(ways));
  for (int x = 0; x < n; ++x) {
    std::vector<int> f(n), g(n);
    if (r[x][x]) ways[x][x] = f[x] = -1;
    else ways[x][x] = f[x] = 1;
    for (int l = 1; l < n; ++l) {
      g.assign(n, 0);
      for (int i = 0; i < m; ++i) if (edges[i].w == 0) {
        int u = edges[i].u, v = edges[i].v;
        if (f[u] == -1 || (f[u] && r[v][v])) g[v] = -1;
        else update(g[v], f[u], mod);
      }
      f.swap(g);
      for (int i = 0; i < n; ++i) {
        if (ways[x][i] == -1) continue;
        if (f[i] == -1) ways[x][i] = -1;
        else update(ways[x][i], f[i], mod);
      }
    }
  }
  int ret = 0;
  for (int i = 0; i < n; ++i) {
    memset(dp[0][i], 0, sizeof(dp[0][i]));
    for (int j = 0; j < n; ++j) {
      update(dp[0][i][0], ways[j][i], mod);
    }
    update(ret, dp[0][i][s - 1], mod);
    if (I == 1) update(ret, mod - 1, mod);
  }
  for (int l = 1; l <= p; ++l) {
    for (int i = 0; i < n; ++i) {
      memset(dp[1][i], 0, sizeof(dp[1][i]));
    }
    for (int i = 0; i < m; ++i) if (edges[i].w > 0) {
      int x = edges[i].u, y = edges[i].v, z = edges[i].w;
      int bound = I / dvs[z];
      int jb = std::upper_bound(dvs.begin(), dvs.end(), bound) - dvs.begin();
      for (int j = 0; j < jb; ++j) if (dp[0][x][j]) {
        int k = go[z][j];
        if (k == -1) continue;
        if (dp[0][x][j] == -1) {
          dp[1][y][k] = -1;
        } else {
          update(dp[1][y][k], dp[0][x][j], mod);
        }
      }
    }
    for (int i = 0; i < n; ++i) {
      memset(dp[0][i], 0, sizeof(dp[0][i]));
    }
    for (int a = 0; a < n; ++a) {
      for (size_t i = 0; i < dvs.size(); ++i) if (dp[1][a][i]) {
        for (int b = 0; b < n; ++b) if (ways[a][b]) {
          if (dp[1][a][i] == -1 || ways[a][b] == -1) dp[0][b][i] = -1;
          else update(dp[0][b][i], 1ll * dp[1][a][i] * ways[a][b] % mod, mod);
        }
      }
    }
    for (int i = 0; i < n && ret != -1; ++i) {
      if (dp[0][i][s - 1] == -1) ret = -1;
      else update(ret, dp[0][i][s - 1], mod);
    }
    if (ret == -1) break;
  }
  if (ret == -1) puts("NIESKONCZONOSC");
  else printf("%d\n", ret);
  return 0;
}

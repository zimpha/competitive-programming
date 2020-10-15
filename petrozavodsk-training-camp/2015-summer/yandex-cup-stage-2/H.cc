#include <cstdio>
#include <cstring>
#include <set>
#include <algorithm>

using i64 = long long;

const int M = 20;
const int mod = 1e9 + 7;

int s[M], fail[M];
int n, m;

void mul(int a[M][M], int b[M][M]) {
  i64 c[M][M];
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < m; ++j) {
      c[i][j] = 0;
      for (int k = 0; k < m; ++k) {
        c[i][j] += (i64)a[i][k] * b[k][j];
        if (k % 8 == 0) c[i][j] %= mod;
      }
    }
  }
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < m; ++j) {
      a[i][j] = c[i][j] % mod;
    }
  }
}

std::set<int> cache;

i64 solve() {
  fail[0] = -1;
  for (int i = 1, j = -1; i <= m; ++i) {
    while (j != -1 && s[j + 1] != s[i]) j = fail[j];
    fail[i] = ++j;
  }
  i64 code = 0;
  for (int i = 1; i <= m; ++i) {
    code = code * i + fail[i];
  }
  if (cache.count(code)) return 0;
  cache.insert(code);
  if (n == m) return 1;
  static int a[M][M], r[M][M];
  memset(a, 0, sizeof(a));
  memset(r, 0, sizeof(r));
  for (int i = 0; i < m; ++i) {
    int j = i, mask = 0;
    while (j >= 0) {
      if (j + 1 < m && (~mask >> s[j + 1] & 1)) {
        a[i][j + 1] = 1;
      }
      mask |= 1 << s[j + 1];
      j = fail[j];
    }
    a[i][0] = 1;
    r[i][i] = 1;
  }
  for (int nn = n - m; nn; nn >>= 1) {
    if (nn & 1) mul(r, a);
    mul(a, a);
  }
  i64 ret = 0;
  for (int i = 0; i < m; ++i) {
    ret += r[fail[m]][i];
  }
  return ret % mod;
}

i64 dfs(int d, int w) {
  if (d == m) return solve();
  i64 ret = 0;
  for (int i = 0; i <= w; ++i) {
    s[d + 1] = i;
    ret += dfs(d + 1, w + (i == w));
  }
  return ret % mod;
}

int main() {
  scanf("%d%d", &n, &m);
  m = std::min(n, m + 1);
  i64 ret = dfs(0, 0);
  printf("%lld\n", ret % mod);
  return 0;
}

#include <cstdio>
#include <vector>
#include <algorithm>

using int64 = long long;

const int N = 2e3 + 10;
const int mod = 1e9 + 7, i2 = 500000004;

int binom[N][N], ways[N][N];

void add(int &x, int y) {
  if ((x += y) >= mod) x -= mod;
}

int main() {
  int n;
  scanf("%d", &n);
  std::vector<bool> mark(n * 2);
  for (int i = 0, x; i < n; ++i) {
    scanf("%d", &x);
    mark[x - 1] = true;
  }
  for (int i = 0; i <= n; ++i) {
    binom[i][0] = binom[i][i] = 1;
    for (int j = 1; j < i; ++j) {
      binom[i][j] = (binom[i - 1][j] + binom[i - 1][j - 1]) % mod;
    }
  }
  ways[0][0] = 1;
  for (int i = 1; i <= n; ++i) {
    for (int j = i; j <= n; ++j) {
      ways[i][j] = (int64)ways[i - 1][j] % mod;
      if (j >= 1) add(ways[i][j], (int64)ways[i - 1][j - 1] * j * 2 % mod);
      if (j >= 2) add(ways[i][j], (int64)ways[i - 1][j - 2] * j * (j - 1) % mod);
    }
  }
  std::vector<int> f(n + 1), g(n + 1);
  f[0] = 1;
  int c0 = 0, c1 = 0;
  for (int i = n * 2 - 1; i >= 0; --i) {
    std::fill(g.begin(), g.end(), 0);
    if (mark[i]) {
      for (int j = c0; j <= c1; ++j) if (f[j]) {
        add(g[j], f[j]);
        for (int k = j + 1; k <= c1 + 1; ++k) {
          add(g[k], (int64)f[j] * binom[c1 - j][k - j - 1] % mod * ways[k - j - 1][k - j - 1] % mod * (k - j + 1) % mod % mod);
        }
      }
      ++c1;
    } else {
      for (int j = c0; j <= c1; ++j) if (f[j]) {
        add(g[j], (int64)f[j] * (j - c0) % mod);
      }
      ++c0;
    }
    f.swap(g);
  }
  int ret = f.back();
  for (int i = 0; i < n; ++i) ret = (int64)ret * i2 % mod;
  printf("%d\n", ret);
  return 0;
}

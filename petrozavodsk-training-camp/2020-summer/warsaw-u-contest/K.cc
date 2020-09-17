#include <cstdio>
#include <cassert>
#include <cstring>
#include <vector>
#include <algorithm>

const int N = 25000 + 10, M = 28;
const int mod = 1e9 + 7;

// vh, mx, removed, odd/even
int f[N][M][M][2], g[N][M][M][2];
int sf[M][2], sg[M][2];
std::vector<int> prefix[N], suffix[N];
int h[N], n, m;

void upd(int &x, int y) {
  if ((x += y) >= mod) x -= mod;
}

void solve(int dp[N][M][M][2], std::vector<int> vh[N]) {
  vh[0] = {0};
  for (int i = 1; i <= n; ++i) {
    vh[i] = vh[i - 1];
    if (std::find(vh[i].begin(), vh[i].end(), h[i]) == vh[i].end()) {
      vh[i].push_back(h[i]);
      std::sort(vh[i].begin(), vh[i].end());
    }
    if (vh[i].size() > m + 1) vh[i].erase(vh[i].begin());
  }
  dp[0][0][0][0] = 1;
  for (int i = 0; i < n; ++i) for (size_t j = 0; j < vh[i].size(); ++j) {
    int j1 = std::lower_bound(vh[i + 1].begin(), vh[i + 1].end(), vh[i][j]) - vh[i + 1].begin();
    int j2 = std::lower_bound(vh[i + 1].begin(), vh[i + 1].end(), h[i + 1]) - vh[i + 1].begin();
    int e1 = vh[i][j] & 1;
    int e2 = h[i + 1] & 1;
    for (int k = 0; k <= m && k <= i; ++k) {
      for (int e = 0; e < 2; ++e) if (dp[i][j][k][e]) {
        // keep
        if (h[i + 1] > vh[i][j]) {
          upd(dp[i + 1][j2][k][e], dp[i][j][k][e]);
        } else {
          upd(dp[i + 1][j1][k][e ^ e1 ^ e2], dp[i][j][k][e]);
        }
        // not keep
        if (k + 1 <= m) {
          upd(dp[i + 1][j1][k + 1][e ^ e1], dp[i][j][k][e]);
        }
      }
    }
  }
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &h[i]);
  }
  solve(f, prefix);
  std::reverse(h, h + n + 2);
  solve(g, suffix);
  std::reverse(h, h + n + 2);
  int ret = 0;
  for (int i = 1; i <= n; ++i) {
    memset(sf, 0, sizeof(sf));
    memset(sg, 0, sizeof(sg));
    for (size_t j = 0; j < prefix[i - 1].size(); ++j) {
      if (prefix[i - 1][j] >= h[i]) break;
      for (int k = 0; k <= m && k <= i - 1; ++k) {
        for (int e = 0; e < 2; ++e) {
          upd(sf[k][e], f[i - 1][j][k][e]);
        }
      }
    }
    for (size_t j = 0; j < suffix[n - i].size(); ++j) {
      if (suffix[n - i][j] > h[i]) break;
      for (int k = 0; k <= m && k <= n - i; ++k) {
        for (int e = 0; e < 2; ++e) {
          upd(sg[k][e], g[n - i][j][k][e]);
        }
      }
    }
    for (int k = 0; k <= m; ++k) {
      upd(ret, (long long)sf[k][0] * sg[m - k][0] % mod);
      upd(ret, (long long)sf[k][1] * sg[m - k][1] % mod);
    }
  }
  printf("%d\n", ret);
  return 0;
}

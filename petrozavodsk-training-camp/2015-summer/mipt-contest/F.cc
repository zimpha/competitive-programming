#include <cstdio>
#include <vector>

using int64 = long long;

const int N = 500 + 10;
const int mod = 1e9 + 7;

int dp[N][N], P[N][N], Q0[N][N], Q1[N][N];
int ext[N][N], cnt[N][N];

void add(int &x, int y) {
  if ((x += y) >= mod) x -= mod;
}

int main() {
  int n, m;
  scanf("%d%d", &m, &n);
  std::vector<std::vector<int>> perm(m, std::vector<int>(n));
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      scanf("%d", &perm[i][j]);
      --perm[i][j];
    }
  }
  std::vector<int> pos(n);
  for (int i = 0; i < n; ++i) pos[perm[0][i]] = i;
  std::vector<std::vector<int>> rank(m, std::vector<int>(n));
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      perm[i][j] = pos[perm[i][j]];
      rank[i][perm[i][j]] = j;
    }
  }
  for (int k = 0; k < m; ++k) {
    for (int i = 0; i < n; ++i) {
      int mx = perm[k][i], mn = perm[k][i];
      for (int j = i; j < n; ++j) {
        mx = std::max(mx, perm[k][j]);
        mn = std::min(mn, perm[k][j]);
        if (mx - mn == j - i) cnt[mn][mx]++;
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    std::vector<int> mx(m), mn(m);
    for (int k = 0; k < m; ++k) mx[k] = mn[k] = rank[k][i];
    for (int j = i; j < n; ++j) {
      for (int k = 0; k < m; ++k) {
        mx[k] = std::max(mx[k], rank[k][j]);
        mn[k] = std::min(mn[k], rank[k][j]);
      }
      if (cnt[i][j] != m) continue;
      ext[i][j] = n;
      for (int k = 0; k < m; ++k) {
        if (rank[k][i] < rank[k][j]) {
          if (mn[k] != 0 && perm[k][mn[k] - 1] > j) ext[i][j] = std::min(ext[i][j], perm[k][mn[k] - 1]);
        } else {
          if (mx[k] != n - 1 && perm[k][mx[k] + 1] > j) ext[i][j] = std::min(ext[i][j], perm[k][mx[k] + 1]);
        }
      }
    }
  }

  for (int i = 0; i < n; ++i) dp[i][i] = 1;
  for (int len = 2; len <= n; ++len) {
    for (int i = 0; i + len <= n; ++i) {
      int j = i + len - 1;
      for (int k = i; k < j; ++k) {
        add(P[i][j], (int64)P[i][k] * dp[k + 1][j] % mod);
        add(Q0[i][j], (int64)dp[i][k] * dp[k + 1][j] % mod);
        if (j < ext[i][k]) {
          add(Q1[i][j], (int64)(Q0[i][k] + Q1[i][k]) * dp[k + 1][j] % mod);
        }
      }
      add(P[i][j], Q0[i][j]);
      if (cnt[i][j] == m) {
        dp[i][j] = (P[i][j] + Q1[i][j]) % mod;
      }
    }
  }
  printf("%d\n", dp[0][n - 1]);
  return 0;
}

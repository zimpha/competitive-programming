#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

const int N = 300 + 10;

std::vector<int> ivs[N];
int cost[N][N][N], dp[N][N];

int solve(int l, int r) {
  if (l > r) return 0;
  if (dp[l][r] != -1) return dp[l][r];
  int &ret = dp[l][r]; ret = 0;
  for (int i = l; i < r; ++i) {
    ret = std::max(ret, solve(l, i) + solve(i + 1, r));
  }
  for (int i = l; i <= r; ++i) if (cost[i][l][r] != -1) {
    ret = std::max(ret, solve(l, i - 1) + solve(i + 1, r) + cost[i][l][r]);
  }
  return ret;
}

int main() {
  freopen("pieaters.in", "r", stdin);
  freopen("pieaters.out", "w", stdout);
  int n, m;
  scanf("%d%d", &n, &m);
  std::vector<int> l(m), r(m), w(m);
  for (int i = 0; i < m; ++i) {
    scanf("%d%d%d", &w[i], &l[i], &r[i]);
  }
  for (int i = 1; i <= n; ++i) {
    std::vector<int> val(n + 1, -1);
    for (int j = 1; j <= n; ++j) ivs[j].clear();
    for (int j = 0; j < m; ++j) {
      if (l[j] <= i && i <= r[j]) ivs[l[j]].push_back(j);
    }
    for (int a = i; a >= 1; --a) {
      for (auto &j: ivs[a]) val[r[j]] = std::max(val[r[j]], w[j]);
      int w = -1;
      for (int b = i; b <= n; ++b) {
        w = std::max(w, val[b]);
        cost[i][a][b] = w;
      }
    }
  }
  memset(dp, -1, sizeof(dp));
  printf("%d\n", solve(1, n));
  return 0;
}

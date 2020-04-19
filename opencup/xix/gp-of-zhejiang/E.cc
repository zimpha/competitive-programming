#include <cstdio>
#include <vector>
#include <algorithm>

using int64 = long long;
const int N = 2001, M = 101;

std::vector<int> edges[2][N];
int64 weight[2][N];
int64 dp[N][M][M], t_dp[N][M][M];
int path[M], mate[M], m;
int64 c1, c2, c3;
int n[2];

void get_path(int u) {
  for (auto &v: edges[0][u]) {
    int l = m;
    path[m++] = v;
    get_path(v);
    int r = m;
    path[m++] = v;
    mate[l] = r;
    mate[r] = l;
  }
}

void dfs(int u) {
  for (auto &v: edges[1][u]) {
    dfs(v);
    for (int i = m - 1; i >= 0; --i) {
      for (int j = m; j >= i; --j) {
        int64 &ret = dp[u][i][j];
        for (int k = i; k < j; ++k) {
          ret = std::min(ret, dp[u][i][k] + t_dp[v][k][j]);
        }
      }
    }
  }
  if (u == 0) return;
  for (int i = 0; i < m; ++i) {
    for (int j = i; j <= m; ++j) {
      int64 &ret = t_dp[u][i][j];
      ret = dp[u][i][j];
      for (int kl = i; kl < j; ++kl) {
        int kr = mate[kl];
        if (kr < kl || kr >= j) continue;
        int64 w = c3 * std::abs(weight[0][path[kl]] - weight[1][u]) - c2 * weight[0][path[kl]] - c1 * weight[1][u];
        ret = std::min(ret, dp[u][kl + 1][kr] + w);
      }
    }
  }
}

int main() {
  scanf("%lld%lld%lld", &c1, &c2, &c3);
  int64 ret = 0;
  for (int i = 0; i < 2; ++i) {
    scanf("%d", &n[i]);
    for (int j = 0, m; j < n[i]; ++j) {
      scanf("%d", &m);
      for (int k = 0, x, w; k < m; ++k) {
        scanf("%d%d", &x, &w);
        edges[i][j].push_back(x - 1);
        weight[i][x - 1] = w;
        ret += (i ? c1 : c2) * w;
      }
    }
  }

  m = 0;
  get_path(0);

  dfs(0);
  ret += dp[0][0][m];
  printf("%lld\n", ret);
  return 0;
}

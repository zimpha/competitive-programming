#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

const int N = 300 + 10;

char s[N][N];
int best[N][N][3];
int dp[N][N][3];
int f[N][N][2];

void update(int &x, int y) {
  if (x == -1 || x > y) x = y;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, m, q;
    scanf("%d%d%d", &m, &n, &q);
    for (int i = 0; i < m; ++i) {
      scanf("%s", s[i]);
    }
    for (int i = 0; i < n; ++i) {
      memset(dp, -1, sizeof(dp));
      dp[m][0][2] = 0;
      for (int j = m; j > 0; --j) {
        int v = s[j - 1][i] == 'B';
        for (int k = 0; k <= m; ++k) {
          for (int e = 0; e < 3; ++e) {
            if (dp[j][k][e] == -1) continue;
            // s[i][j - 1] skip
            update(dp[j - 1][k + 1][e], dp[j][k][e]);
            // s[i][j - 1] do
            update(dp[j - 1][k][v], dp[j][k][e] + (v != e));
          }
        }
      }
      for (int k = 0; k <= m; ++k) {
        for (int e = 0; e < 3; ++e) {
          best[i][k][e] = dp[0][k][e];
        }
      }
    }
    memset(f, -1, sizeof(f));
    f[0][0][0] = f[0][0][1] = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j <= m; ++j) {
        for (int e = 0; e < 2; ++e) {
          if (f[i][j][e] == -1) continue;
          for (int k = 0; k <= m; ++k) {
            int u = best[i][k][2];
            if (u != -1) {
              update(f[i + 1][std::max(j, u + 1)][e], f[i][j][e] + k);
            }
            for (int o = 0; o < 2; ++o) {
              int u = best[i][k][o];
              if (u == -1) continue;
              update(f[i + 1][std::max(j, u + 1)][e], f[i][j][e] + k);
            }
          }
        }
      }
    }
    std::vector<int> ans(n * m, -1);
    for (int i = 0; i < n * m; ++i) {
      for (int j = 0; j <= m; ++j) {
        for (int e = 0; e < 2; ++e) {
          printf("j=%d e=%d f=%d\n", j, e, f[n][j][e]);
          if (ans[i] == -1 && f[n][j][e] != -1 && f[n][j][e] <= i) ans[i] = j;
        }
      }
    }
    printf("Case #%d:", cas);
    for (int i = 0; i < q; ++i) {
      int x;
      scanf("%d", &x);
      printf(" %d", ans[x]);
    }
    puts("");
  }
  return 0;
}

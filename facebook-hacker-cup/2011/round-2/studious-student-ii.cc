#include <cstdio>
#include <cstring>

using int64 = long long;

const int N = 70, mod = 1e9 + 7;

int dp[N][N][N][2][2][2];
int binom[N][N];
char s[N];

void update(int &x, int y) {
  if ((x += y) >= mod) x -= mod;
}

int main() {
  for (int i = 0; i < N; ++i) {
    binom[i][0] = binom[i][i] = 1;
    for (int j = 1; j < i; ++j) {
      binom[i][j] = (binom[i - 1][j] + binom[i - 1][j - 1]) % mod;
    }
  }
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    scanf("%s", s);
    int n = strlen(s);
    memset(dp, 0, sizeof(dp));
    for (int i = 0; i < n; ++i) {
      dp[i][i][0][s[i] == 'a'][s[i] == 'b'][1] = 1;
    }
    for (int len = 2; len <= n; ++len) {
      for (int i = 0; i + len <= n; ++i) {
        int j = i + len - 1;
        for (int step = 0; step < len; ++step) for (int mask = 2; mask < 8; ++mask) {
          int one = mask & 1, a = mask >> 1 & 1, b = mask >> 2;
          if (dp[i + 1][j][a][b][one] == 0) continue;
          update(dp[i][j][step][a || s[i] == 'a'][b || s[i] == 'b'][0], dp[i + 1][j][step][a][b][one]);
        }
        for (int k = i; k <= j; ++k) for (int step = 0; step < len; ++step) {
          for (int mask = 1; mask < 4; ++mask) {
            int a = mask & 1, b = mask >> 1;
            int cnt = dp[i][k][step][a][b][0];
            for (int to = 0; to < 2 && cnt; ++to) {
              if ((a == 0 && to == 0) || (b == 0 && to == 1)) continue;
              if (k == j) update(dp[i][j][step + 1][!to][to][1], cnt);
              else {
                for (int t_step = 0 ; t_step < len; ++t_step) for (int t_mask = 2; t_mask < 8; ++t_mask) {
                    int t_one = t_mask & 1, t_a = t_mask >> 1 & 1, t_b = t_mask >> 2;
                    int t_cnt = dp[k + 1][j][t_step][t_a][t_b][t_one];
                    if (!t_cnt) continue;
                    update(dp[i][j][t_step + step + 1][t_a || !to][t_b || to][0],
                        (int64)cnt * t_cnt % mod * binom[t_step + step + 1][t_step] % mod);
                }
              }
            }
          }
        }
      }
    }
    int ret = 0;
    for (int step = 0; step < n; ++step) for (int mask = 2; mask < 8; ++mask) {
      int one = mask & 1, a = mask >> 1 & 1, b = mask >> 2;
      update(ret, dp[0][n - 1][step][a][b][one]);
    }
    printf("Case #%d: %d\n", cas, ret);
  }
  return 0;
}
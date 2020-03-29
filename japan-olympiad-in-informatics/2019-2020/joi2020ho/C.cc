#include <iostream>
#include <cstring>
#include <algorithm>

using int64 = long long;

const int N = 210;

int64 dp[N][N][2][N];
int x[N], t[N];

void upd(int64 &x, int64 y) {
  if (x == -1 || x > y) x = y;
}

signed main(){
  int n, l;
  scanf("%d%d", &n, &l);
  for (int i = 1; i <= n; ++i) scanf("%d", &x[i]);
  for (int i = 1; i <= n; ++i) scanf("%d", &t[i]);
  x[n + 1] = l;
  memset(dp, -1, sizeof(dp));
  dp[0][n + 1][0][0] = dp[0][n + 1][1][0] = 0;
  for (int i = 0; i < n; ++i){
    for (int j = n + 1; j >= i + 2; --j){
      for (int m = 0; m <= n; ++m) {
        int64 tmp = -1;
        if (dp[i][j][0][m] != -1) upd(tmp, dp[i][j][0][m] + x[i + 1] - x[i]);
        if (dp[i][j][1][m] != -1) upd(tmp, dp[i][j][1][m] + l - x[j] + x[i + 1]);
        if (tmp != -1) upd(dp[i + 1][j][0][m + (tmp <= t[i + 1])], tmp);
        tmp = -1;
        if (dp[i][j][0][m] != -1) upd(tmp, dp[i][j][0][m] + l - x[j - 1] + x[i]);
        if (dp[i][j][1][m] != -1) upd(tmp, dp[i][j][1][m] + x[j] - x[j - 1]);
        if (tmp != -1) upd(dp[i][j - 1][1][m + (tmp <= t[j - 1])], tmp);
      }
    }
  }
  int ret = 0;
  for (int i = 0; i <= n + 1; ++i){
    for (int j = 0; j <= n + 1; ++j){
      for (int k = 0; k < 2; ++k){
        for (int m = ret; m <= n; ++m){
          if (dp[i][j][k][m] != -1) ret = m;
        }
      }
    }
  }
  printf("%d\n", ret);
  return 0;
}

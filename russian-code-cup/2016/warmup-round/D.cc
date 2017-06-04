#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MAXN = 2000 + 10, M = 1e9 + 7;

LL S[MAXN][MAXN], dp[MAXN][MAXN][4];
int a[MAXN], b[MAXN], n, m;

LL cc(LL x) {
  if (x == 1) return 1;
  else return x * (x - 1) % M;
}
void upd(LL &x, LL y) {
  x = (x + y) % M;
}

int main() {
  S[0][0] = 1;
  for (int n = 1; n < MAXN; ++n) {
    for (int k = 1; k <= n; ++k) {
      S[n][k] = (S[n - 1][k - 1] + S[n - 1][k] * k) % M;
    }
  }
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) scanf("%d", a + i);
  sort(a, a + n);
  int s = 0; b[0] = 1;
  for (int i = 1; i < n; ++i) {
    if (a[i] == a[i - 1]) b[s]++;
    else b[++s] = 1;
  }
  n = s + 1;
  for (int i = 1; i <= b[0]; ++i) {
    dp[0][i][0] = dp[0][i][2] = 0;
    dp[0][i][1] = S[b[0]][i] * i % M;
    dp[0][i][3] = S[b[0]][i];
  }
  s = b[0];
  for (int i = 1; i < n; ++i) {
    for (int j = 1; j <= s; ++j) {
      for (int k = 1; k <= b[i]; ++k) {
        LL w = S[b[i]][k];
        upd(dp[i][j + k][1], dp[i - 1][j][0] * w % M * k % M);
        upd(dp[i][j + k][3], dp[i - 1][j][0] * w % M);

        upd(dp[i][j + k - 1][0], dp[i - 1][j][1] * w % M * k % M);
        upd(dp[i][j + k - 1][2], dp[i - 1][j][1] * w % M * cc(k) % M);

        upd(dp[i][j + k - 1][0], dp[i - 1][j][2] * w % M * k % M);
        upd(dp[i][j + k - 1][2], dp[i - 1][j][2] * w % M * cc(k) % M);

        upd(dp[i][j + k][1], dp[i - 1][j][3] * w % M * k % M);
        upd(dp[i][j + k][3], dp[i - 1][j][3] * w % M);
      }
    }
    s += b[i];
  }
  printf("%lld\n", (dp[n - 1][m][0] + dp[n - 1][m][3]) % M);
  return 0;
}

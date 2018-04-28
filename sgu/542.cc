#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MAXN = 200000 + 10;

LL a[MAXN], dp[61][MAXN];

void run() {
  int n; scanf("%d", &n); dp[0][0] = 1;
  for (int i = 1; i <= n; ++i) scanf("%lld", a + i);
  for (int i = 0; i < 60; ++i) {
    int c0, c1 = 0, nx = 0;
    for (int j = 1; j <= n; ++j) c1 += a[j] >> i & 1;
    if (!(c1 & 1)) dp[i + 1][0] += dp[i][0];
    if (!((n - c1) & 1)) dp[i + 1][n - c1] += dp[i][0];
    for (int j = 1; j <= n; ++j) {
      if (a[j] >> i & 1) --c1;
      else ++c1, nx++;
      if (!(c1 & 1)) dp[i + 1][nx] += dp[i][j];
      if (!((n - c1) & 1)) dp[i + 1][nx + n - c1] += dp[i][j];
    }
    static LL p0[MAXN], p1[MAXN]; c1 = c0 = 0;
    for (int j = 1; j <= n; ++j) {
      if (a[j] >> i & 1) p1[c1++] = a[j];
      else p0[c0++] = a[j];
    }
    for (int j = 1; j <= c0; ++j) a[j] = p0[j - 1];
    for (int j = 1; j <= c1; ++j) a[j + c0] = p1[j - 1];
  }
  LL sg = 0;
  for (int j = 1; j <= n; ++j) sg ^= a[j] - a[1];
  printf("%lld\n", dp[60][0] - !sg);
}

int main() {
  run();
  return 0;
}

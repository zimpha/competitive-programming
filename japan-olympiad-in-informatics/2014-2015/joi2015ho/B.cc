#include <cstdio>
#include <cstring>
#include <algorithm>

using int64 = long long;

const int N = 2000 + 10;

int64 dp[N][N];
int a[N], n;

int64 solve(int i, int j) {
  i %= n;
  if (j == 1) return a[i];
  if (j == 2) return std::max(a[i], a[(i + 1) % n]);
  if (dp[i][j] != -1) return dp[i][j];
  int64 left = 0, right = 0;
  // take left
  if (a[(i + 1) % n] < a[(i + j - 1) % n]) left = solve(i + 1, j - 2) + a[i];
  else left = solve(i + 2, j - 2) + a[i];
  // take right
  if (a[i] < a[(i + j - 2) % n]) right = solve(i, j - 2) + a[(i + j - 1) % n];
  else right = solve(i + 1, j - 2) + a[(i + j - 1) % n];
  return dp[i][j] = std::max(left, right);
}

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }
  memset(dp, -1, sizeof(dp));
  int64 ret = 0;
  for (int i = 0; i < n; ++i) {
    ret = std::max(ret, solve(i, n));
  }
  printf("%lld\n", ret);
  return 0;
}

#include <cstdio>
#include <algorithm>

const int N = 1e6 + 10;

int cnt[N][2], dp[N][2];
int a[N], n, k;

void update(int &x, int y) {
  if (x == -1 || x > y) x = y;
}

int main() {
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
    cnt[i % k][a[i] & 1]++;
    a[i] = (a[i] & 1) ^ a[i - 1];
  }
  for (int i = 0; i < k; ++i) {
    dp[i][0] = dp[i][1] = -1;
  }
  dp[0][0] = 0;
  for (int i = 1; i < k; ++i) {
    if (dp[i - 1][0] != -1) {
      update(dp[i][0], dp[i - 1][0] + cnt[i][1]);
      update(dp[i][1], dp[i - 1][0] + cnt[i][0]);
    }
    if (dp[i - 1][1] != -1) {
      update(dp[i][0], dp[i - 1][1] + cnt[i][0]);
      update(dp[i][1], dp[i - 1][1] + cnt[i][1]);
    }
  }
  if (k == 1) printf("%d\n", cnt[0][1]);
  else {
    printf("%d\n", std::min(dp[k - 1][0] + cnt[0][1], dp[k - 1][1] + cnt[0][0]));
  }
  return 0;
}

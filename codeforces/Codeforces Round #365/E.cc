#include <bits/stdc++.h>

using LL = long long;
using PIL = std::pair<int, LL>;

const int N = 1000 + 10, M = 10000;
std::map<LL, int> idx;
PIL dp[N][M];
LL a[N], b[N], k;
int n, m;

void run() {
  std::cin >> n >> k;
  std::vector<LL> factor;
  for (LL i = 1; i * i <= k; ++i) if (k % i == 0) {
    factor.push_back(i);
    if (i * i != k) factor.push_back(k / i);
  }
  std::sort(factor.begin(), factor.end());
  m = factor.size();
  for (int i = 0; i < m; ++i) idx[factor[i]] = i;
  for (int i = 1; i <= n; ++i) {
    std::cin >> a[i];
    b[i] = std::__gcd(a[i], k);
  }
  if (k == 1) {
    std::cout << 1 << std::endl;
    std::cout << std::min_element(a + 1, a + n + 1) - a << std::endl;
    return;
  }
  for (int i = 1; i < m; ++i) dp[0][i] = {n + 1, 0};
  dp[0][0] = {0, 0};
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j < m; ++j) {
      int p = idx[factor[j] / std::__gcd(factor[j], b[i])];
      dp[i][j] = dp[i - 1][j];
      if (dp[i][j] > PIL(dp[i - 1][p].first + 1, dp[i - 1][p].second + a[i])) {
        dp[i][j] = {dp[i - 1][p].first + 1, dp[i - 1][p].second + a[i]};
      }
    }
  }
  if (dp[n][m - 1].first > n) std::cout << -1 << std::endl;
  else {
    std::cout << dp[n][m - 1].first << std::endl;
    for (int i = n, j = m - 1; i; --i) {
      if (dp[i - 1][j] == dp[i][j]) continue;
      j = idx[factor[j] / std::__gcd(factor[j], b[i])];
      std::cout << i << ' ';
    }
  }
  std::cout << std::endl;
}

int main() {
  run();
  return 0;
}

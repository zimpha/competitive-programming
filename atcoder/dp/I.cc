#include <cstdio>
#include <vector>

int main() {
  int n;
  scanf("%d", &n);
  std::vector<double> dp(n + 1);
  dp[0] = 1;
  for (int i = 0; i < n; ++i) {
    std::vector<double> g(n + 1);
    double p;
    scanf("%lf", &p);
    for (int j = 0; j <= i; ++j) {
      g[j] += dp[j] * (1 - p);
      g[j + 1] += dp[j] * p;
    }
    dp.swap(g);
  }
  double ret = 0;
  for (int i = n / 2 + 1; i <= n; ++i) ret += dp[i];
  printf("%.10f\n", ret);
  return 0;
}

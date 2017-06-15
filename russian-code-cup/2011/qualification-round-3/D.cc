#include <cstdio>
#include <vector>
#include <algorithm>

int main() {
  int n, p;
  scanf("%d%d", &n, &p);
  std::vector<int> mass(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &mass[i]);
  }
  std::vector<int> weight(1 << n);
  for (int i = 0; i < (1 << n); ++i) {
    weight[i] = 0;
    for (int j = 0; j < n; ++j) {
      if (i >> j & 1) weight[i] += mass[j];
    }
  }
  std::vector<int> dp(1 << n, 1e9);
  dp[0] = 0;
  for (int mask = 1; mask < (1 << n); ++mask) {
    for (int sub = mask; sub; sub = (sub - 1) & mask) {
      dp[mask] = std::min(dp[mask], dp[mask ^ sub] + (weight[sub] == 1000 ? p : weight[sub]));
    }
  }
  printf("%d\n", dp.back());
  return 0;
}

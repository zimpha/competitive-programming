#include <cstdio>
#include <bitset>
#include <vector>

using int64 = long long;

int main() {
  int m, l, k, s;
  scanf("%d%d%d%d", &m, &l, &k, &s);
  std::vector<int> c(m);
  std::vector<std::bitset<401>> dp(m);
  for (int i = 0; i < m; ++i) {
    scanf("%d", &c[i]);
    dp[i][0] = 1;
  }
  std::vector<int> tickets(m);
  for (int i = 0; i < l; ++i) {
    int p, r;
    scanf("%d%d", &p, &r);
    tickets[p - 1] += r;
    if (r <= k) {
      dp[p - 1] |= dp[p - 1] << r;
    }
  }
  int64 ret = 0;
  for (int i = 0; i < m; ++i) {
    int64 best = 0;
    for (int j = 0; j <= k && j <= tickets[i]; ++j) if (dp[i][j]) {
      tickets[i] -= j;
      int64 x = tickets[i] / k;
      int64 y = tickets[i] % k;
      auto tmp = x * k * c[i] - x * s;
      if (y) tmp += y * c[i] - s;
      if (tmp > best) best = tmp;
      tickets[i] += j;
    }
    ret += best;
  }
  printf("%lld\n", ret);
  return 0;
}

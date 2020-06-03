#include <cstdio>
#include <bitset>
#include <vector>

using int64 = long long;

const int N = 2e5 + 10;
using state = std::bitset<N>;

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int k;
    int64 n, s;
    scanf("%lld%lld%d", &n, &s, &k);
    std::vector<int> a(k);
    for (int i = 0; i < k; ++i) scanf("%d", &a[i]);
    state dp; dp[0] = 1;
    while (n || s) {
      if (n & 1) {
        state t_dp;
        for (auto &x: a) t_dp ^= dp << x;
        dp = t_dp;
      }
      state t_dp;
      for (int j = 0; j < N / 2; ++j) {
        t_dp[j] = dp[j * 2 + (s & 1)];
      }
      dp = t_dp;
      n >>= 1; s >>= 1;
    }
    printf("%d\n", (int)dp[0]);
  }
  return 0;
}

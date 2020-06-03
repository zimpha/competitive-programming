#include <cstdio>
#include <vector>
#include <cstring>

const int N = 1 << 20;

int dp[N];

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    memset(dp, 0, sizeof(dp));
    int n;
    scanf("%d", &n);
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) scanf("%d", &a[i]), dp[a[i]]++;
    for (int i = 0; i < 20; ++i) {
      for (int j = 0; j < N; ++j) {
        if (j >> i & 1) dp[j] += dp[j ^ (1 << i)];
      }
    }
    long long ret = 0;
    for (auto &x: a) ret += dp[x];
    printf("%lld\n", ret);
  }
  return 0;
}

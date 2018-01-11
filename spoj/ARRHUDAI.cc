// max_{x=1}^{n} {(sum_{i=1}^{n} |a[i] - a[x]|^p ) % k}
#include <cstdio>
#include <vector>
#include <algorithm>

using int64 = long long;

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, p, k, m = 0;
    scanf("%d%d%d", &n, &p, &k);
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
      scanf("%d", &a[i]);
      m = std::max(m, a[i]);
    }
    std::vector<int64> cnt(m + 1), pw(m + 1);
    for (int i = 0; i <= m; ++i) {
      pw[i] = 1;
      for (int j = 0; j < p; ++j) pw[i] = pw[i] * i % k;
    }
    for (auto &&x: a) cnt[x]++;
    int64 ret = 0;
    for (int i = 1; i <= m; ++i) if (cnt[i]) {
      int64 sum = 0;
      for (int j = 1; j <= m; ++j) {
        sum += pw[std::abs(i - j)] * cnt[j] % k;
      }
      sum %= k;
      if (sum >= ret) ret = sum;
    }
    printf("Case %d: %lld\n", cas, ret);
  }
  return 0;
}

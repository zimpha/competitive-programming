#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>

using i64 = long long;

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    i64 sum = k - 1, mi = n;
    for (int i = 0, x; i < m; ++i) {
      scanf("%d", &x);
      sum += std::abs(x - k) * 2;
      mi = std::min<int>(mi, x);
    }
    printf("%lld\n", sum - std::abs(mi - k) + mi - 1);
  }
  return 0;
}

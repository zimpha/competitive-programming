#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>

using int64 = long long;

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    std::vector<int64> C(n), J(n);
    for (int i = 0; i < n; ++i) {
      scanf("%lld %lld\n", &C[i], &J[i]);
    }
    std::set<std::pair<int, int>> s;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (C[i] < C[j] && J[i] > J[j]) {
          int x = J[i] - J[j];
          int y = C[j] - C[i];
          int g = std::__gcd(x, y);
          s.emplace(x / g, y / g);
        }
      }
    }
    printf("Case #%d: %d\n", cas, (int)s.size() + 1);
  }
  return 0;
}

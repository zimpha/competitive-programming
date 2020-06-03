#include <cstdio>
#include <vector>
#include <algorithm>

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    std::vector<int> r(n), c(n);
    for (int i = 0; i < n; ++i) {
      scanf("%d%d", &r[i], &c[i]);
    }
    int a = *std::max_element(r.begin(), r.end());
    int b = *std::min_element(r.begin(), r.end());
    int o = (a + b) / 2 + ((a + b) & 1);
    int r1 = 0;
    for (int i = 0; i < n; ++i) {
      r1 = std::max(r1, abs(r[i] - o));
    }
    a = *std::max_element(c.begin(), c.end());
    b = *std::min_element(c.begin(), c.end());
    o = (a + b) / 2 + ((a + b) & 1);
    int r2 = 0;
    for (int i = 0; i < n; ++i) {
      r2 = std::max(r2, abs(c[i] - o));
    }
    printf("Case #%d: %d\n", cas, std::max(r1, r2));
  }
  return 0;
}
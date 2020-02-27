#include <cstdio>
#include <algorithm>
#include <vector>

using int64 = long long;

int main() {
  int64 n;
  scanf("%lld", &n);
  int64 ret = n, x = 1, y = n;
  std::vector<int64> g;
  for (int64 i = 2; i * i <= n; ++i) if (n % i == 0) {
    int64 p = 1;
    while (n % i == 0) n /= i, p *= i;
    g.push_back(p);
  }
  if (n > 1) g.push_back(n);
  for (int mask = 0; mask < (1 << g.size()); ++mask) {
    int64 a = 1, b = 1;
    for (size_t i = 0; i < g.size(); ++i) {
      if (mask >> i & 1) a *= g[i];
      else b *= g[i];
    }
    if (a < b) std::swap(a, b);
    if (a < ret) ret = a, x = a, y = b;
  }
  printf("%lld %lld\n", x, y);
  return 0;
}

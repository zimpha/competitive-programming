#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <vector>
#include <set>

using int64 = long long;

int main() {
  int64 n;
  scanf("%lld", &n);
  std::set<int64> sum;
  for (int d = 1; d * d <= n; ++d) if (n % d == 0) {
    // 1, 1 + d, 1 + kd <= n
    int64 k = (n - 1) / d;
    sum.insert((1 + 1 + k * d) * (k + 1) / 2);
    k = (n - 1) / (n / d);
    sum.insert((1 + 1 + k * (n / d)) * (k + 1) / 2);
  }
  for (auto &&x: sum) printf("%lld ", x);
  puts("");
  return 0;
}
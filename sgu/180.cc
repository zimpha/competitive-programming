#include <cstdio>
#include <vector>
#include <algorithm>

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }
  std::vector<int> xs(a);
  std::sort(xs.begin(), xs.end());
  for (int i = 0; i < n; ++i) {
    a[i] = std::lower_bound(xs.begin(), xs.end(), a[i]) - xs.begin();
  }
  std::fill(xs.begin(), xs.end(), 0);
  long long ret = 0;
  for (int i = 0; i < n; ++i) {
    for (int x = a[i] + 1; x < n; x += ~x & x + 1) ret += xs[x];
    for (int x = a[i]; x >= 0; x -= ~x & x + 1) xs[x] += 1;
  }
  printf("%lld\n", ret);
  return 0;
}

#include <cstdio>
#include <vector>
#include <algorithm>

int main() {
  int n;
  scanf("%d", &n);
  std::vector<std::pair<double, double>> a(n);
  std::vector<int> idx(n);
  for (int i = 0; i < n; ++i) {
    idx[i] = i;
    scanf("%lf%lf", &a[i].first, &a[i].second);
  }
  std::sort(idx.begin(), idx.end(), [&](int x, int y) {
      return a[x].second * a[y].first < a[x].first * a[y].second;
  });
  for (int i = 0; i < n; ++i) printf("%d\n", idx[i] + 1);
  return 0;
}

#include <cstdio>
#include <vector>
#include <algorithm>

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> a(n), b(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d%d", &a[i], &b[i]);
  }
  int ret = 0;
  int l = 0, r = a[0] + b[0];
  for (int i = 1; i < n; ++i) {
    int x = std::max(0, a[i] + b[i] - r);
    int y = std::min(a[i] + b[i], a[i] + b[i] - l);
    if (x <= y) ++ret, l = x, r = y;
    else l = 0, r = a[i] + b[i];
  }
  printf("%d\n", ret);
  return 0;
}

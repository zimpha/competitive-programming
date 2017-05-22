#include <cstdio>
#include <set>
#include <vector>
#include <algorithm>

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }
  std::sort(a.begin(), a.end());
  int ret = 0;
  for (int i = 0; i < n; ++ret) {
    if (i + 1 < n && a[i + 1] - a[i] <= 2) i += 2;
    else i += 1;
  }
  printf("%d\n", ret);
  return 0;
}

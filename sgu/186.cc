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
  std::sort(a.begin(), a.end());
  int ret = 0;
  for (int i = 0, j = n - 1; i < j; ) {
    if (--a[i] == 0) ++i;
    --j;
    ++ret;
  }
  printf("%d\n", ret);
  return 0;
}

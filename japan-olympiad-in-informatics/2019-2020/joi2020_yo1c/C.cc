#include <cstdio>
#include <vector>

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
  int ret = 1;
  for (int i = 0, j; i < n; i = j) {
    for (j = i + 1; j < n && a[j - 1] <= a[j]; ++j);
    if (j - i > ret) ret = j - i;
  }
  printf("%d\n", ret);
  return 0;
}

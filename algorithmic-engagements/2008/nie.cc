#include <cstdio>
#include <vector>
#include <algorithm>

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  std::vector<int> a(n), b(m);
  for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
  for (int i = 0; i < m; ++i) scanf("%d", &b[i]);
  std::sort(a.begin(), a.end());
  std::sort(b.begin(), b.end());
  int ret = -1;
  for (int i = 0, j = 0; j < m; ++j) {
    while (i < n && a[i] <= b[j]) ++i;
    if (i && (ret == -1 || b[j] - a[i - 1] < ret)) ret = b[j] - a[i - 1];
    if (i < n && (ret == -1 || a[i] - b[j] < ret)) ret = a[i] - b[j];
  }
  printf("%d\n", ret);
  return 0;
}

#include <cstdio>
#include <vector>

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  std::vector<int> a(n), b(m);
  for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
  for (int i = 0; i < m; ++i) scanf("%d", &b[i]);
  int i = 0, j = 0;
  for (; i < n && j < m; ) {
    if (a[i] < b[j]) printf("%d\n", a[i++]);
    else printf("%d\n", b[j++]);
  }
  while (i < n) printf("%d\n", a[i++]);
  while (j < m) printf("%d\n", b[j++]);
  return 0;
}

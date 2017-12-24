#include <cstdio>
#include <vector>
#include <algorithm>

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> a(n), id(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
    id[i] = i;
  }
  std::sort(id.begin(), id.end(), [&](int x, int y) {
    return a[x] < a[y] || (a[x] == a[y] && x > y);
  });
  for (int i = 0; i < n; ++i) {
    if (i) putchar(' ');
    printf("%d", id[i] + 1);
  }
  puts("");
  return 0;
}

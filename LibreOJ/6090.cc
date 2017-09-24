#include <cstdio>
#include <vector>

int main() {
  int n, k;
  scanf("%d%d", &n, &k);
  if (k > 1) {
    puts("Yes");
    return 0;
  }
  std::vector<int> a(n);
  int zero = -1;
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
    if (a[i] == 0) zero = i;
  }
  scanf("%d", &a[zero]);
  bool flag = true;
  for (int i = 1; i < n; ++i) {
    if (a[i] <= a[i - 1]) flag = false;
  }
  if (!flag) puts("Yes");
  else puts("No");
  return 0;
}

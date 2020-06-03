#include <cstdio>
#include <vector>

int main() {
  int k;
  scanf("%d", &k);
  int n = 2000;
  int s = k + n;
  std::vector<int> a(n);
  a[0] = -1;
  for (int i = 1; i < n; ++i) a[i] = s / (n - 1);
  for (int i = 1; i <= s % (n - 1); ++i) ++a[i];
  printf("%d\n", n);
  for (int i = 0; i < n; ++i) {
    if (i) putchar(' ');
    printf("%d", a[i]);
  }
  puts("");
  return 0;
}

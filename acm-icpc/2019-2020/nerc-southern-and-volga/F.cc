#include <cstdio>
#include <algorithm>

int main() {
  int n;
  scanf("%d", &n);
  int ret = (n + 1) * 2;
  for (int i = 1; i <= n; ++i) if (n % i == 0) {
    ret = std::min(ret, 2 * (i + n / i));
  }
  printf("%d\n", ret);
  return 0;
}

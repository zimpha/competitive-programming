#include <cstdio>

int main() {
  int n;
  scanf("%d", &n);
  int ret = 1;
  for (int i = 1; i <= n; ++i) {
    ret = ret * i % 10;
  }
  printf("%d\n", ret);
  return 0;
}

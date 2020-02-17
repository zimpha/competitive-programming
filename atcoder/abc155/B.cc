#include <cstdio>

int main() {
  int n;
  scanf("%d", &n);
  int ret = 1;
  for (int i = 0, x; i < n; ++i) {
    scanf("%d", &x);
    ret &= (x % 2 == 1) || (x % 3 == 0) || (x % 5 == 0);
  }
  if (ret) puts("APPROVED");
  else puts("DENIED");
  return 0;
}

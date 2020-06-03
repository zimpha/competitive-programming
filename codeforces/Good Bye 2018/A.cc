#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <iostream>

int main() {
  int y, b, r;
  scanf("%d%d%d", &y, &b, &r);
  int ret = 0;
  for (int i = 0; i <= 100; ++i) {
    if (i <= y && i + 1 <= b && i + 2 <= r) ret = i;
  }
  printf("%d\n", ret * 3 + 3);
  return 0;
}

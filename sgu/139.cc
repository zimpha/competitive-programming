#include <cstdio>

int main() {
  int a[16];
  int zero = 0, inv = 0;
  for (int i = 0; i < 16; ++i) {
    scanf("%d", &a[i]);
    if (a[i] == 0) zero = i;
    for (int j = 0; j < i; ++j) inv += a[j] > a[i];
  }
  zero = 3 - zero / 4 + 3 - zero % 4;
  if ((inv ^ (15 - zero) ^ 1) & 1) puts("YES");
  else puts("NO");
  return 0;
}

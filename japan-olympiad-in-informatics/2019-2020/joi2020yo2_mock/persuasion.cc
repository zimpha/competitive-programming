#include <cstdio>

int main() {
  int n;
  scanf("%d", &n);
  int c1 = 0, c2 = 0;
  int A, B;
  scanf("%d%d", &A, &B);
  for (int i = 1; i < n; ++i) {
    int a, b;
    scanf("%d%d", &a, &b);
    if (a > A) ++c1;
    if (b > B) ++c2;
  }
  printf("%d\n", c1 < c2 ? c1 : c2);
  return 0;
}

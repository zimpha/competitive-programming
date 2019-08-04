#include <cstdio>

int main() {
  int x = 1, y = 0;
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= m; ++i) {
    int z = (x + y) % 10;
    x = y;
    y = z;
    if (i >= n) printf("%d", z);
  }
  puts("");
  return 0;
}

#include <cstdio>

int main() {
  int n, m, p;
  scanf("%d%d%d", &n, &m, &p);
  int ret = 0;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      if ((i + j) * 2 >= p) ret += (n - i + 1) * (m - j + 1);
    }
  }
  printf("%d\n", ret);
  return 0;
}

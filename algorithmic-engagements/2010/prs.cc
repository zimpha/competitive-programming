#include <cstdio>
#include <algorithm>

int main() {
  int n, m, p;
  scanf("%d%d%d", &n, &m, &p);
  long long ret = 0;
  for (int i = 1; i <= n; ++i) {
    for (int j = std::max(1, p / 2 - i); j <= m; ++j) {
      if ((i + j) * 2 >= p) ret += (n - i + 1) * (m - j + 1);
    }
  }
  printf("%lld\n", ret);
  return 0;
}

#include <cstdio>
#include <algorithm>

int main() {
  int p, m, c, k, r, v;
  scanf("%d%d%d%d%d%d", &p, &m, &c, &k, &r, &v);
  printf("%d\n", std::min(p / k, std::min(m / r, c / v)));
  return 0;
}

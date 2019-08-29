#include <cstdio>
#include <vector>

using int64 = long long;

int main() {
  int m, l, k, s;
  scanf("%d%d%d%d", &m, &l, &k, &s);
  std::vector<int> c(m);
  for (int i = 0; i < m; ++i) {
    scanf("%d", &c[i]);
  }
  std::vector<int> tickets(m);
  for (int i = 0; i < l; ++i) {
    int p, r;
    scanf("%d%d", &p, &r);
    tickets[p - 1] += r;
  }
  int64 ret = 0;
  for (int i = 0; i < m; ++i) {
    int64 x = tickets[i] / k;
    int64 y = tickets[i] % k;
    ret += x * k * c[i] - x * s;
    if (y * c[i] >= s) ret += y * c[i] - s;
  }
  printf("%lld\n", ret);
  return 0;
}

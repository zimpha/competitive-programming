#include <cstdio>
#include <algorithm>

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  int total = 0;
  double ret = 0;
  for (int i = 0; i < n; ++i) {
    int price, type;
    scanf("%d%d", &price, &type);
    total += price;
    if (type == 1) ret += 0.8 * price;
    else ret += price;
  }
  for (int i = 0; i < m; ++i) {
    int b, c;
    scanf("%d%d", &b, &c);
    if (total >= b) {
      ret = std::min<double>(ret, total - c);
    }
  }
  printf("%.2f\n", ret);
  return 0;
}

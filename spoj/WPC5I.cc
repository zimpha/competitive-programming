#include <cstdio>
#include <algorithm>

using int64 = long long;

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, m;
    scanf("%d%d", &n, &m);
    int64 ret = 1;
    for (int i = 2; (n != 1 || m != 1) && i * i <= std::max(n, m); ++i) {
      int cn = 0, cm = 0;
      while (n % i == 0) n /= i, ++cn;
      while (m % i == 0) m /= i, ++cm;
      if (cn != cm) {
        for (int e = 0; e < std::max(cn, cm); ++e) ret *= i;
      }
    }
    if (n != m) ret *= n, ret *= m;
    printf("%lld\n", ret);
  }
}

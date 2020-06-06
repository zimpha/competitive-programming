#include <cmath>
#include <cstdio>
#include <algorithm>

using int64 = long long;
using flt = long double;

const flt eps = 1e-12;

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  int64 ret = 0;
  if (n % 2 == 0) {
    for (int p = -m; p <= m; ++p) {
      flt x = powl((flt)std::abs(p) / n, flt(1.0) / (n - 1));
      if (p > 0) x = -x;
      flt y = -x * (p - flt(p) / n);
      int64 q = floorl(y + 0.5);
      if (-m <= q && q <= m && std::abs(y - q) <= eps) ++ret;
    }
  } else {
    for (int p = -m; p <= m; ++p) {
      if (p >= 0) { ret += m * 2 + 1; continue; }  
      flt x = powl((flt)std::abs(p) / n, flt(1.0) / (n - 1));
      flt y = -x * (p - flt(p) / n);
      if (y < 0) ret += m * 2 + 1;
      else {
        int64 bound = int64(y + eps);
        if (bound < m) ret += 2 * (m - bound);
      }
    }
  }
  printf("%lld\n", ret);
  return 0;
}

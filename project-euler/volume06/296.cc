#include <bits/stdc++.h>

long dfs(long a, long b, long c, long d, int n) {
  long x = a + c, y = b + d, xy = x + y;
  if (xy * 5 > n) return 0;
  long ret = 0;
  for (long t = 3; ; ++t) {
    int l = (t * y - 1) / xy, r = std::min(t - 1, n / xy - t);
    if (r >= l) ret += r - l;
    else break;
  }
  return ret + dfs(a, b, x, y, n) + dfs(x, y, c, d, n);
}

//BE = ac / (a+b)
int naive(int n) {
  long ret = 0;
  for (int a = 1; a <= n / 3; ++a) {
    for (int b = a; b <= (n - a) / 2; ++b) {
      int v = std::min(a + b, n - a - b + 1);
      int g = std::__gcd(a, a + b);
      int z = (a + b) / g;
      int r = v / z, l = (b + z - 1) / z;
      if (v % z == 0) --r;
      if (r >= l) ret += r - l + 1;
    }
  }
  return ret;
}

long run(int n) {
  long ret = 0;
  for (int a = 2; ; ++a) {
    int l = (a - 1) / 2, r = std::min(n / 2 - a, a - 1);
    if (r >= l) ret += r - l;
    else break;
  }
  return dfs(0, 1, 1, 1, n) + ret;
}

int main() {
  std::cout << run(100000) << std::endl;
  return 0;
}

#include <bits/stdc++.h>

using LL = long long;

const LL M = 100000000;

LL P(LL f, LL r) {
  LL t1 = (__int128)f * f / 2 % M;
  LL a = f / 2 * 2 + 1;
  if (f == 1) t1 = 1, a = 2;
  if (r == 1) return t1;
  --r;
  LL res = 0;
  if (r & 1) {
    t1 = (a % M) * (a % M) % M - t1;
    t1 += M; t1 %= M; ++a;
    r /= 2;
    res = r % M * (2 * r % M - 1 + 2 * a % M) % M;
    res += t1;
    res %= M;
  } else {
    r /= 2;
    // 2a + 1, 2a + 5, ..., 2a + 1 + 2r
    res = r % M * (2 * r % M - 1 + 2 * a % M) % M;
    res += t1;
    res %= M;
  }
  return res;
}

LL run(LL n) {
  LL ret = 0;
  for (LL g = 1; g * g <= n; ++g) {
    if (n % g == 0) {
      ret += P(g, n / g);
      if (g * g != n) ret += P(n / g, g);
      ret %= M;
    }
  }
  return ret;
}

int main() {
  std::cout << P(1, 1) << std::endl;
  std::cout << P(1, 2) << std::endl;
  std::cout << P(2, 3) << std::endl;
  std::cout << P(10, 20) << std::endl;
  std::cout << P(25, 75) << std::endl;
  std::cout << P(99, 100) << std::endl;
  std::cout << run(71328803586048ll) << std::endl;
  return 0;
}

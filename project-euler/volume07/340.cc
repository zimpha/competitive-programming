#include <bits/stdc++.h>

using LL = long long;

const int M = 1000000000;

// F(n) = n + 4(k+1)a-(3k+4)c, k >= 0, a > c
LL run(LL a, LL b, LL c) {
  LL n = b / a, ret = 0;
  for (LL i = 0; i <= n; ++i) {
    LL l = b - a + 1, r = b;
    l = std::max(l, 0ll);
    LL add = 4 * (i + 1) % M * a % M - (3 * i + 4) % M * c % M;
    add %= M; add += M; add %= M;
    LL x = r + l, y = (r - l + 1);
    if (x % 2 == 0) x /= 2;
    else y /= 2;
    ret += (x % M) * (y % M) % M + add * (r - l + 1) % M;
    ret %= M;
    b -= a;
  }
  return ret;
}

int main() {
  std::cout << run(50, 2000, 40) << std::endl;
  std::cout << run(1801088541, 558545864083284007ll, 35831808) << std::endl;
  return 0;
}

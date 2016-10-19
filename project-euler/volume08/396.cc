#include <bits/stdc++.h>

using LL = long long;
const int M = 1e9;

LL pow_mod(LL a, LL n) {
  LL r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % M;
    a = a * a % M;
  }
  return r;
}

//https://en.wikipedia.org/wiki/Fast-growing_hierarchy
LL f(LL n, LL k, LL p = 1) {
  if (p > 1) return f(f(n, k, p - 1), k, 1);
  if (k == 0) return (n + 1) % M;
  if (k == 2) return pow_mod(2, n) * n % M;
  return f(n, k - 1, n);
}

//https://en.wikipedia.org/wiki/Goodstein%27s_theorem
LL G(int n) {
  LL ret = 3;
  for (int i = 0; n; n >>= 1, ++i) {
    if (n & 1) ret = f(ret, i);
  }
  return ret - 3;
}

LL run(int n) {
  LL ret = 0;
  for (int i = 1; i < n; ++i) {
    ret += G(i);
  }
  return ret % M;
}

int main() {
  std::cout << run(16) << std::endl;
}

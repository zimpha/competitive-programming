#include <bits/stdc++.h>

using LL = long long;
const int M = 1000000000, iv = 888888889;

LL pm(LL a, LL n) {
  LL r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % M;
    a = a * a % M;
  }
  return r;
}

LL f(LL n) {
  // f(n) = (11 ^ n - 2 ^ n)) / 9
  LL ret = pm(11, n) - pm(2, n);
  ret = ret * iv % M;
  return (ret + M) % M;
}

LL run(int n) {
  LL ret = 0, pw = 1;
  for (int i = 0; i < n; ++i) {
    pw *= 13;
    ret += f(pw);
  }
  return ret %= M;
}

int main() {
  std::cout << f(5) << std::endl;
  std::cout << run(17) << std::endl;
  return 0;
}

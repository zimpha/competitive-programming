#include <bits/stdc++.h>

using LL = long long;

const int M = 1000000000;

LL sum(LL n) {
  LL a = n, b = n + 1, c = n * 2 + 1;
  if (a % 2 == 0) a /= 2;
  else if (b % 2 == 0) b /= 2;
  if (a % 3 == 0) a /= 3;
  else if (b % 3 == 0) b /= 3;
  else c /= 3;
  a %= M, b %= M, c %= M;
  return a * b % M * c % M;
}

LL run(LL n) {
  LL ret = 0;
  for (LL i = 1, j; i <= n; i = j + 1) {
    j = n / (n / i);
    ret += (n / j) % M * (sum(j) - sum(i - 1) + M) % M;
    ret %= M;
  }
  return ret;
}

int main() {
  std::cout << run(1) << std::endl;
  std::cout << run(2) << std::endl;
  std::cout << run(3) << std::endl;
  std::cout << run(4) << std::endl;
  std::cout << run(5) << std::endl;
  std::cout << run(6) << std::endl;
  std::cout << run(1000000000000000ll) << std::endl;
  return 0;
}

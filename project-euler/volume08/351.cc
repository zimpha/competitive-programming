#include <bits/stdc++.h>

using LL = long long;

std::map<LL, LL> cache;

LL calc(LL n) {
  if (cache.count(n)) return cache[n];
  LL ret = n * n - n * (n + 1) / 2;
  for (LL i = 2, j; i <= n; i = j + 1) {
    j = n / (n / i);
    ret -= calc(n / j) * (j - i + 1);
  }
  return cache[n] = ret;
}

LL run(LL n) {
  LL ret = n * n - n * (n + 1) / 2 - calc(n);
  return ret * 6 + 6 * (n - 1);
}

int main() {
  std::cout << run(5) << std::endl;
  std::cout << run(10) << std::endl;
  std::cout << run(1000) << std::endl;
  std::cout << run(100000000) << std::endl;
  return 0;
}


#include <bits/stdc++.h>

using LL = long long;

LL run(LL n) {
  n -= 1;
  LL ret = 0;
  std::vector<LL> fib = {1, 1};
  for (int i = 2; i < 100; ++i) {
    fib.push_back(fib[i - 1] + fib[i - 2]);
  }
  std::vector<LL> sum = {1, 1};
  for (int i = 2; i < 100; ++i) {
    sum.push_back(sum[i - 1] + sum[i - 2] + fib[i - 2]);
  }
  int m = 0;
  for (; ; ++m) {
    n -= fib[m];
    if (n < 0) {
      n += fib[m];
      break;
    }
    ret += sum[m];
  }
  if (!n) return ret;
  LL add = 0;
  for (; n; ) {
    if (n < fib[m - 1]) {
      m -= 1;
    } else {
      ret += sum[m - 1] + fib[m - 1] * add;
      n -= fib[m - 1];
      m -= 2;
      add += 1;
    }
  }
  return ret;
}

int main() {
  std::cout << run(12) << std::endl;
  std::cout << run(22) << std::endl;
  std::cout << run(33) << std::endl;
  std::cout << run(44) << std::endl;
  std::cout << run(1000000) << std::endl;
  std::cout << run(100000000000000000ll) << std::endl;
  return 0;
}

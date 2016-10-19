#include <bits/stdc++.h>

using LL = long long;

LL get_step(LL n) {
  n = n * 2 - 1;
  for (LL i = 2; i * i <= n; ++i) {
    if (n % i == 0) {
      if (i >= 3) return (i - 1) / 2;
      while (n % i == 0) n /= i;
    }
  }
  return (n - 1) / 2;
}

LL run(LL n) {
  LL g = 9;
  while (true) {
    LL step = get_step(g);
    if (step + g > n) break;
    g += step;
  }
  return g * 3 + n - g;
}

int main() {
  std::cout << run(1000000) << std::endl;
  std::cout << run(1000000000000000ll) << std::endl;
  return 0;
}

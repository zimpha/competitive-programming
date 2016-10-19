#include <bits/stdc++.h>

long double run(int n, int k) {
  long double tot = k * log(n), fac = 0;
  for (int i = n - k + 1; i <= n; ++i) fac += log(i);
  long double ret = exp(fac - tot);
  int p = n - k + 1, d = 1;
  long double sum = 0, tmp = 0;
  for (int i = 0; i < k; i += 2) {
    sum += log(k - i) + log(k - i - 1) - log(2);
    fac -= log(p);
    tmp += log(d);
    ret += exp(sum + fac - tmp - tot);
    ++p, ++d;
  }
  return 1 - ret;
}

int main() {
  std::cout.precision(10);
  std::cout << run(7, 3) << std::endl;
  std::cout << run(1000000, 20000) << std::endl;
  return 0;
}

#include <bits/stdc++.h>

using LL = long long;
const int N = 100000000;
int p[N], mark[N], m;

void sieve() {
  m = 0;
  for (int i = 2; i < N; ++i) {
    if (!mark[i]) p[m++] = i;
    for (int j = 0; j < m && p[j] * i < N; ++j) {
      mark[i * p[j]] = 1;
      if (i % p[j] == 0) break;
    }
  }
}

LL run(int n) {
  std::vector<LL> x(n), y(n);
  x[0] = y[0] = 2;
  for (int i = 1; i < n; ++i) {
    x[i] = x[i - 1] + p[i * 2 - 1] + p[i * 2];
    y[i] = y[i - 1] - p[i * 2 - 1] + p[i * 2];
  }
  LL ret = 0;
  for (int a = 0; a + 1 < n; ++a) {
    int j = a + 1;
    ++ret;
    for (int i = a + 2; i < n; ++i) {
      LL x1 = x[j] - x[a], y1 = y[j] - y[a];
      LL x2 = x[i] - x[a], y2 = y[i] - y[a];
      __int128 val = (__int128)x1 * y2 - (__int128)y1 * x2;
      if (val >= 0) {
        ++ret, j = i;
      }
      if (i - j >= 5000) break;
    }
  }
  return ret;
}

int main() {
  sieve();
  std::cout << "number of primes: " << m << std::endl;
  std::cout << run(100) << std::endl;
  std::cout << run(2500000) << std::endl;
  return 0;
}


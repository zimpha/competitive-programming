#include <bits/stdc++.h>

using LL = long long;

const int M = 1e8 + 7;

int fac[M], inv[M];

LL C(int n, int m) {
  if (n < m) return 0;
  return (LL)fac[n] * inv[fac[m]] % M * inv[fac[n - m]] % M;
}

LL lucas(LL n, LL m) {
  if (n == 0 && m == 0) return 1;
  return lucas(n / M, m / M) * C(n % M, m % M) % M;
}

LL C(LL n) {
  // C(n) = 8 * C(2n, n) - 3n^2 - 2n - 7
  LL ret = lucas(n * 2, n) * 8 % M;
  n %= M;
  ret -= 3 * n * n % M + 2 * n % M + 7;
  ret %= M; ret += M;
  return ret % M;
}

LL run(int n) {
  std::vector<LL> fib = {1, 1};
  for (int i = 2; i < n; ++i) {
    fib.push_back(fib[i - 1] + fib[i - 2]);
  }
  LL ret = 0;
  for (int i = 1; i < n; ++i) {
    LL val = C(fib[i]);
    std::cout << "C(" << fib[i] << ")=" << val << std::endl;
    ret += val;
  }
  return ret %= M;
}

int main() {
  fac[0] = fac[1] = inv[1] = 1;
  for (int i = 2; i < M; ++i) {
    fac[i] = 1ll * i * fac[i - 1] % M;
    inv[i] = LL(M - M / i) * inv[M % i] % M;
  }
  std::cout << C(1) << std::endl;
  std::cout << C(2) << std::endl;
  std::cout << C(10) << std::endl;
  std::cout << run(90) << std::endl;
  return 0;
}

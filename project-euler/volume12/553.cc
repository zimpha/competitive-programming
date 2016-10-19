#include <bits/stdc++.h>

long solve(long n) {
  std::vector<long> f(1 << n), g(1 << n);
  f[0] = 1;
  for (int i = 1; i < (1 << n); ++i) {
    g = f;
    for (int x = 0; x < (1 << n); ++x) {
      g[x | i] += f[x];
    }
    f = g;
  }
  return f[(1 << n) - 1];
}

const int M = 1e9 + 7, N = 10001;

long fpm(long a, long n, long m) {
  long r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % m;
    a = a * a % m;
  }
  return r;
}

long fac[N], inv[N], g[N], pw[N];

void prepare() {
  // g[n] = A003465(n)
  fac[0] = inv[0] = g[0] = pw[0] = 1;
  for (int i = 1; i < N; ++i) {
    fac[i] = fac[i - 1] * i % M;
    inv[i] = fpm(fac[i], M - 2, M);
    pw[i] = fpm(2, fpm(2, i, M - 1) - 1 + M - 1, M);
    for (int k = 0; k <= i; ++k) {
      long val = fac[i] * inv[k] % M * inv[i - k] % M * pw[i - k] % M;
      if (k & 1) g[i] -= val;
      else g[i] += val;
    }
    g[i] %= M; g[i] += M; g[i] %= M;
  }
}

long f[N][N];

long C(long n, long m) {
  return fac[n] * inv[m] % M * inv[n - m] % M;
}

long dp(long n, long m) {
  if (n < m) return f[n][m] = 0;
  if (f[n][m] != -1) return f[n][m];
  f[n][m] = 0;
  if (m == 1) {
    f[n][m] = g[n];
    for (int i = 1; i <= n - 1; ++i) {
      f[n][m] += M - dp(i, 1) * g[n - i] % M * C(n - 1, i - 1) % M;
      f[n][m] %= M;
    }
  } else {
    for (int i = 1; i < n; ++i) {
      f[n][m] += dp(n - i, m - 1) * C(n - 1, i - 1) % M * dp(i, 1) % M;
      f[n][m] %= M;
    }
  }
  return f[n][m];
}

long run(long n, long k) {
  long ret = 0;
  for (int i = 1; i <= n; ++i) {
    ret += dp(i, k) * C(n, i) % M;
    ret %= M;
  }
  return ret;
}

int main() {
  memset(f, -1, sizeof(f));
  prepare();
  std::cout << run(2, 1) << std::endl;
  std::cout << run(3, 1) << std::endl;
  std::cout << run(4, 2) << std::endl;
  std::cout << run(100, 10) << std::endl;
  std::cout << run(10000, 10) << std::endl;
  return 0;
}

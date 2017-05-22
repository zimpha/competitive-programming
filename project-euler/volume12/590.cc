#include <bits/stdc++.h>

long phi(long n) {
  long r = n;
  for (long i = 2; i * i <= n; ++i) {
    if (n % i) continue;
    while (n % i == 0) n /= i;
    r = r / i * (i - 1);
  }
  if (n > 1) r = r / n * (n - 1);
  return r;
}

long f[2][1953125], g[2][1953125];

long solve2(std::vector<long> &pl) {
  if (pl.empty()) return 1;
  long mod = 512;
  for (int i = 0; i < 9; ++i) {
    f[0][i] = f[1][i] = 0;
  }
  if (pl[0] + 1 < 9) f[0][pl[0] + 1] = 1;
  if (pl[0] < 9) f[1][pl[0]] = 1;
  for (size_t it = 1; it < pl.size(); ++it) {
    long c = pl[it];
    for (int i = 0; i < 9; ++i) {
      g[0][i] = g[1][i] = 0;
    }
    for (long j = 0; j < 9; ++j) {
      if (j * (c + 1) < 9) {
        g[0][j * (c + 1)] += f[0][j];
        g[1][j * (c + 1)] += f[1][j];
      }
      if (j * c < 9) {
        g[1][j * c] += f[0][j];
        g[0][j * c] += f[1][j];
      }
    }
    for (int j = 0; j < 9; ++j) {
      f[0][j] = g[0][j] % mod;
      f[1][j] = g[1][j] % mod;
    }
  }
  long ret = 0, pw = 1;
  for (long j = 0; j < 9; ++j) {
    ret += pw * f[0][j] % mod;
    ret -= pw * f[1][j] % mod;
    pw = pw * 2 % mod;
  }
  return (ret % mod + mod) % mod;
}

long solve5(std::vector<long> &pl) {
  const int mod = 1953125;
  if (pl.empty()) return 1;
  int p = phi(mod);
  for (int i = 0; i < p; ++i) {
    f[0][i] = f[1][i] = 0;
  }
  f[0][(pl[0] + 1) % p] = 1;
  f[1][pl[0] % p] = 1;
  for (size_t it = 1; it < pl.size(); ++it) {
    long c = pl[it];
    for (int i = 0; i < p; ++i) {
      g[0][i] = g[1][i] = 0;
    }
    for (long j = 0; j < p; ++j) {
      g[0][j * (c + 1) % p] += f[0][j];
      g[1][j * (c + 1) % p] += f[1][j];

      g[1][j * c % p] += f[0][j];
      g[0][j * c % p] += f[1][j];
    }
    for (int j = 0; j < p; ++j) {
      f[0][j] = g[0][j] % mod;
      f[1][j] = g[1][j] % mod;
    }
  }
  long ret = 0, pw = 1;
  for (long j = 0; j < p; ++j) {
    ret += pw * f[0][j] % mod;
    ret -= pw * f[1][j] % mod;
    pw = pw * 2 % mod;
  }
  return (ret % mod + mod) % mod;
}

long solve(std::vector<long> &pl) {
  long s2 = solve2(pl);
  long s5 = solve5(pl);
  long mod = 1000000000;
  std::cerr << s2 << ' ' << s5 << std::endl;
  return (1953125 * s2 * 109 + 512 * s5 * 1537323) % mod;
}

long HL(long n) {
  std::vector<long> pl;
  std::vector<bool> mark(n + 1, false);
  for (long i = 2; i <= n; ++i) {
    if (mark[i]) continue;
    long c = 1;
    for (long j = i; j * i <= n; j *= i) ++c;
    pl.push_back(c);
    for (long j = i; j <= n; j += i) mark[j] = true;
  }
  return solve(pl);
}

long pow_mod(long a, long n, long m) {
  long r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % m;
    a = a * a % m;
  }
  return r;
}

long brute(std::vector<long> &pl) {
  int n = pl.size();
  long ret = 0;
  for (auto &&c: pl) std::cout << c << ' ';
  std::cout << std::endl;
  const int mod = 1000000000;
  for (int mask = 0; mask < (1 << n); ++mask) {
    long sgn = 1, pw = 1;
    for (int i = 0; i < n; ++i) {
      if (mask >> i & 1) sgn *= -1, pw = pw * pl[i];
      else pw = pw * (pl[i] + 1);
    }
    ret += sgn * pow_mod(2, pw, mod);
  }
  ret %= mod;
  ret += mod;
  return ret % mod;
}

long H(long n) {
  std::vector<long> pl;
  for (long i = 2; i * i <= n; ++i) {
    if (n % i) continue;
    long c = 0;
    while (n % i == 0) n /= i, ++c;
    pl.push_back(c);
  }
  if (n > 1) pl.push_back(1);
  return solve(pl);
}

int main() {
  std::cout << H(12252240) << std::endl;
  std::cout << HL(17) << std::endl;
  std::cout << HL(50000) << std::endl;  
  return 0;
}

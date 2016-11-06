#include <bits/stdc++.h>

const int N = 200, mod = 1000000007;

long fpm(long a, long n) {
  long r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % mod;
    a = a * a % mod;
  }
  return r;
}

void mul(long A[N][N], long B[N][N], int m) {
  static long C[N][N];
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < m; ++j) {
      C[i][j] = 0;
      for (int k = 0; k < m; ++k) {
        C[i][j] += A[i][k] * B[k][j] % mod;
      }
    }
  }
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < m; ++j) {
      A[i][j] = C[i][j] % mod;
    }
  }
}

long solve1(long n, int m) {// m <= 100
  static long A[N][N], R[N], T[N];
  memset(A, 0, sizeof(A));
  memset(R, 0, sizeof(R));
  for (int i = 1; i <= m; ++i) {
    R[(i - 1) * 2 + (i & 1)] = 1;
  }
  for (int j = 1; j <= m; ++j) {
    for (int k = 1; k <= m; ++k) {
      for (int e = 0; e < 2; ++e) {
        if (j <= k) A[(j - 1) * 2 + e][(k - 1) * 2 + e] += 1;
        else A[(j - 1) * 2 + (e ^ (j - k) % 2)][(k - 1) * 2 + e] += 1;
      }
    }
  }
  for (n -= 1; n; n >>= 1) {
    if (n & 1) {
      for (int i = 0; i < m * 2; ++i) {
        T[i] = 0;
        for (int j = 0; j < m * 2; ++j) {
          T[i] += A[i][j] * R[j] % mod;
        }
      }
      for (int i = 0; i < m * 2; ++i) {
        R[i] = T[i] % mod;
      }
    }
    mul(A, A, m * 2);
  }
  long ret = 0;
  for (int i = 0; i < m; ++i) ret += R[i * 2];
  return ret % mod;
}

long solve2(int n, int m) {// n, m <= 10000
  long f[m + 1][2], g[m + 1][2];
  long so[m + 1], se[m + 1];
  memset(f, 0, sizeof(f));
  for (int i = 1; i <= m; ++i) f[i][i & 1] = 1;
  for (int i = 2; i <= n; ++i) {
    memset(g, 0, sizeof(g));
    for (int e = 0; e < 2; ++e) {
      so[0] = se[0] = 0;
      for (int j = 1; j <= m; ++j) {
        so[j] = so[j - 1], se[j] = se[j - 1];
        if (j & 1) so[j] += f[j][e];
        else se[j] += f[j][e];
        so[j] %= mod, se[j] %= mod;
      }
      for (int j = 1; j <= m; ++j) {
        g[j][e] += so[m] - so[j - 1] + se[m] - se[j - 1];
        g[j][e ^ (j & 1)] += se[j - 1];
        g[j][e ^ (j & 1) ^ 1] += so[j - 1];
      }
    }
    for (int j = 0; j <= m; ++j) {
      f[j][0] = (g[j][0] % mod + mod) % mod;
      f[j][1] = (g[j][1] % mod + mod) % mod;
    }
  }
  long ret = 0;
  for (int i = 1; i <= m; ++i) {
    ret += f[i][0];
  }
  return ret % mod;
}

std::vector<long> interpolation(std::vector<long> &x, std::vector<long> &y) {
  long n = x.size();
  std::vector<long> u(y), ret(n), sum(n);
  ret[0] = u[0], sum[0] = 1;
  for (int i = 1; i < n; ++i) {
    for (int j = n - 1; j >= i; --j) {
      u[j] = (u[j] - u[j - 1]) * fpm(x[j] - x[j - i], mod - 2) % mod;
    }
    for (int j = i; j; --j) {
      sum[j] = (-sum[j] * x[i - 1] + sum[j - 1]) % mod;
      ret[j] = (ret[j] + sum[j] * u[i]) % mod;
    }
    sum[0] = -sum[0] * x[i - 1] % mod;
    ret[0] = (ret[0] + sum[0] * u[i]) % mod;
  }
  return ret;
}

long solve3(int n, long m) {// n <= 100
  int s = n;
  std::vector<long> x(s), y(s);
  for (int i = 0; i < s; ++i) {
    long h = (i + 1) * s + (m & 1);
    x[i] = h;
    y[i] = (solve2(n, h) - solve2(n, h - 1) + mod) % mod;
  }
  std::vector<long> coef = interpolation(x, y);
  long ret = 0, pw = 1;
  for (int i = 0; i < s; ++i) {
    ret = (ret + coef[i] * pw) % mod;
    pw = pw * (m % mod) % mod;
  }
  return (ret + mod) % mod;
}

long F(long n, long m) {
  if (m <= 10000 && n <= 10000) return (solve2(n, m) - solve2(n, m - 1) + mod) % mod;
  if (m <= 100) return (solve1(n, m) - solve1(n, m - 1) + mod) % mod;
  return solve3(n, m);
}

int main() {
  std::cout << F(4, 2) << std::endl;
  std::cout << F(13, 10) << std::endl;
  std::cout << F(10, 13) << std::endl;
  std::cout << F(100, 100) << std::endl;
  std::cout << F(1000000000000ll, 100) << std::endl;
  std::cout << F(10000, 10000) << std::endl;
  std::cout << F(100, 1000000000000ll) << std::endl;
  std::cout << F(100, 100000000000ll) << std::endl;
  return 0;
}

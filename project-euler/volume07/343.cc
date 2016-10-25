#include <bits/stdc++.h>

const int N = 10000000;

int mp[N], p[N], m;

template<typename T>
T gcd(T a, T b) {
  return !b ? a : gcd(b, a % b);
}

inline long mul_mod(long a, long b, long mod) {
  assert(0 <= a && a < mod);
  assert(0 <= b && b < mod);
  if (mod < int(1e9)) return a * b % mod;
  long k = (long)((long double)a * b / mod);
  long res = a * b - k * mod;
  res %= mod;
  if (res < 0) res += mod;
  return res;
}

long pow_mod(long a, long n, long m) {
  long res = 1;
  for (a %= m; n; n >>= 1) {
    if (n & 1) res = mul_mod(res, a, m);
    a = mul_mod(a, a, m);
  }
  return res;
}

struct Primality {
public:
  // 用miller rabin素数测试判断n是否为质数
  bool is_prime(long n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (~n & 1) return false;
    const int u[] = {2,3,5,7,325,9375,28178,450775,9780504,1795265022,0};
    long e = n - 1, a, c = 0; // 原理：http://miller-rabin.appspot.com/
    while (~e & 1) e >>= 1, ++c;
    for (int i = 0; u[i]; ++i) {
      if (n <= u[i]) return true;
      a = pow_mod(u[i], e, n);
      if (a == 1) continue;
      for (int j = 1; a != n - 1; ++j) {
        if (j == c) return false;
        a = mul_mod(a, a, n);
      }
    }
    return true;
  }
  // 求一个小于n的因数，期望复杂度为O(n^0.25)，当n为非合数时返回n本身
  long pollard_rho(long n){
    if (n <= 3 || is_prime(n)) return n; // 保证n为合数时可去掉这行
    while (1) {
      int i = 1, cnt = 2;
      long x = rand() % n, y = x, c = rand() % n;
      if (!c || c == n - 2) ++c;
      do {
        long u = gcd(n - x + y, n);
        if (u > 1 && u < n) return u;
        if (++i == cnt) y = x, cnt <<= 1;
        x = (c + mul_mod(x, x, n)) % n;
      } while (x != y);
    }
    return n;
  }
  // 使用rho方法对n做质因数分解，建议先筛去小质因数后再用此函数
  std::vector<long> factorize(long n){
    std::vector<long> u;
    if (n > 1) u.push_back(n);
    for (size_t i = 0; i < u.size(); ++i){
      long x = pollard_rho(u[i]);
      if(x == u[i]) continue;
      u[i--] /= x;
      u.push_back(x);
    }
    std::sort(u.begin(), u.end());
    return u;
  }
} pl;

void sieve() {
  for (int i = 2; i < N; ++i) {
    if (!mp[i]) mp[i] = i, p[m++] = i;
    for (int j = 0; j < m && p[j] * i < N; ++j) {
      mp[i * p[j]] = p[j];
      if (i % p[j] == 0) break;
    }
  }
}

long largest(long n) {
  long ret = 0;
  if (n < N) {
    while (n != 1) {
      ret = mp[n];
      n /= mp[n];
    }
    return ret;
  } else {
    for (long i = 0; i < m && (long)p[i] * p[i] <= n; ++i) {
      while (n % p[i] == 0) n /= p[i], ret = p[i];
    }
    if (n > 1) ret = n;
  }
  return ret;
}

long calc(long n) {
  long ret = largest(n + 1);
  return std::max(ret, largest(n * n - n + 1)) - 1;
}

long run(long n) {
  long ret = 0;
  for (long i = 1; i <= n; ++i) ret += calc(i);
  return ret;
}

int main() {
  sieve();
  std::cout << run(100) << std::endl;
  std::cout << run(2000000) << std::endl;
  return 0;
}

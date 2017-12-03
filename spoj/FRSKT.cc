#include <cstdio>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <functional>
#include <map>

using int64 = long long;
using pii = std::pair<int64, int>;

template<typename T>
T gcd(T a, T b) {
  return !b ? a : gcd(b, a % b);
}

inline int64 mul_mod(int64 a, int64 b, int64 mod) {
  if (mod < int(1e9)) return a * b % mod;
  int64 k = (int64)((long double)a * b / mod);
  int64 res = a * b - k * mod;
  res %= mod;
  if (res < 0) res += mod;
  return res;
}

int64 pow_mod(int64 a, int64 n, int64 m) {
  int64 res = 1;
  for (a %= m; n; n >>= 1) {
    if (n & 1) res = mul_mod(res, a, m);
    a = mul_mod(a, a, m);
  }
  return res;
}

struct Primality {
public:
  // 用miller rabin素数测试判断n是否为质数
  bool is_prime(int64 n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (~n & 1) return false;
    const int u[] = {2,3,5,7,325,9375,28178,450775,9780504,1795265022,0};
    int64 e = n - 1, a, c = 0; // 原理：http://miller-rabin.appspot.com/
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
  int64 pollard_rho(int64 n){
    if (n <= 3 || is_prime(n)) return n; // 保证n为合数时可去掉这行
    while (1) {
      int i = 1, cnt = 2;
      int64 x = rand() % n, y = x, c = rand() % n;
      if (!c || c == n - 2) ++c;
      do {
        int64 u = gcd(n - x + y, n);
        if (u > 1 && u < n) return u;
        if (++i == cnt) y = x, cnt <<= 1;
        x = (c + mul_mod(x, x, n)) % n;
      } while (x != y);
    }
    return n;
  }
  // 使用rho方法对n做质因数分解，建议先筛去小质因数后再用此函数
  std::vector<pii> factorize(int64 n){
    static const int sp[25] = {	2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
    std::vector<pii> fac;
    for (int i = 0; i < 25 && n > 1; ++i) {
      if (n % sp[i]) continue;
      int c = 0;
      while (n % sp[i] == 0) n /= sp[i], ++c;
      fac.emplace_back(sp[i], c);
    }
    std::vector<int64> u;
    if (n > 1) u.push_back(n);
    for (size_t i = 0; i < u.size(); ++i){
      int64 x = pollard_rho(u[i]);
      if(x == u[i]) continue;
      u[i--] /= x;
      u.push_back(x);
    }
    std::sort(u.begin(), u.end());
    for (size_t i = 0, j, m = u.size(); i < m; i = j) {
      for (j = i; j < m && u[i] == u[j]; ++j);
      fac.emplace_back(u[i], j - i);
    }
    return fac;
  }
  std::vector<int64> divisors(int64 n) {
    if (n == 1) return {1};
    auto fac = factorize(n);
    int m = fac.size();
    std::vector<int64> ds;
    std::function<void(int, int64)> dfs = [&](int d, int64 now) {
      if (d == m) {
        ds.emplace_back(now);
        return;
      }
      for (int i = 0, u = fac[d].second; i <= u; ++i) {
        dfs(d + 1, now);
        now *= fac[d].first;
      }
    };
    dfs(0, 1);
    std::sort(ds.begin(), ds.end());
    return ds;
  }
} pf;

void fib(int64 n, int64 &x, int64 &y, int64 mod) {// store in x, n-th
  if (n == 0) {
    x = 0, y = 1;
    return;
  } else if (n & 1) {
    fib(n - 1, y, x, mod);
    y += x;
    if (y >= mod) y -= mod;
  } else {
    int64 a, b;
    fib(n >> 1, a, b, mod);
    y = mul_mod(a, a, mod) + mul_mod(b, b, mod);
    x = mul_mod(a, b, mod) + mul_mod(a, b - a + mod, mod);
    if (y >= mod) y -= mod;
    if (x >= mod) x -= mod;
  }
}

std::map<int64, int64> mem;
int64 period_p(int64 p) {
  static const int cache[] = {1, 3, 8, 6, 20, 24, 16, 12, 24, 60};
  if (p <= 10) return cache[p - 1];
  if (mem.count(p)) return mem[p];
  auto ds = (p % 5 == 1 || p % 5 == 4) ? pf.divisors(p - 1) : pf.divisors(2 * p + 2);
  for (auto &&d: ds) {
    int64 x, y;
    fib(d, x, y, p);
    if (x == 0 && y == 1) return mem[p] = d;
  }
  return -1;
}

int64 period(int64 n) {
  auto fac = pf.factorize(n);
  int64 pi = 1;
  for (auto &&e: fac) {
    int64 u = period_p(e.first);
    for (int i = 1; i < e.second; ++i) {
      u *= e.first;
    }
    int64 g = gcd(pi, u);
    pi = pi / g * u;
  }
  return pi;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int64 k, n, m;
    scanf("%lld%lld%lld", &k, &n, &m);
    std::vector<int64> mod(k + 1);
    mod[0] = m;
    for (int i = 1; i < k; ++i) {
      mod[i] = period(mod[i - 1]);
    }
    int64 s = n;
    for (int i = k - 1; i >= 0; --i) {
      int64 x, y;
      fib(s, x, y, mod[i]);
      s = x;
    }
    printf("%lld\n", s % m);
  }
  return 0;
}

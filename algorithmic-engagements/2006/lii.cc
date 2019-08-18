#include <cstdio>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>

using uint32 = unsigned int;
using int64 = long long;
using uint64 = unsigned long long;

// mod should be not greater than 2^62 (about 4e18)
// return a * b % mod when mod is less than 2^31
inline uint64 mul_mod(uint64 a, uint64 b, uint64 mod) {
  assert(0 <= a && a < mod);
  assert(0 <= b && b < mod);
  if (mod < int(1e9)) return a * b % mod;
  uint64 k = (uint64)((long double)a * b / mod);
  uint64 res = a * b - k * mod;
  if ((int64)res < 0) res += mod;
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

int64 gcd(int64 x, int64 y) {
  return y ? gcd(y, x % y) : x;
}

int64 euler_phi(int64 n) {
  int64 ret = n;
  for (int64 i = 2; i * i <= n; ++i) if (n % i == 0) {
    ret = ret / i * (i - 1);
    while (n % i == 0) n /= i;
  }
  if (n > 1) ret = ret / n * (n - 1);
  return ret;
}

bool test(int64 g, int64 n, int64 phi, std::vector<int64> &u) {
  for (size_t i = 0; i < u.size(); ++i) {
    if (pow_mod(g, phi / u[i], n) == 1) return false;
  }
  return true;
}

int64 primitive_root(int64 n) {
  int64 phi = euler_phi(n), m = phi;
  std::vector<int64> u;
  for (int64 i = 2; i * i <= m; ++i) if (m % i == 0) {
    u.push_back(i);
    while (m % i == 0) m /= i;
  }
  if (m > 1) u.push_back(m);
  for (int g = 1; ; ++g) {
    if (test(g, n, phi, u)) return g;
  }
  return -1;
}

// 求离散对数，即 a^x % m = r的最小非负整数解x，返回-1说明无解
int64 log(int64 a, int64 r, int64 m){
  if (r >= m) return -1;
  int64 i, g, x, c = 0, at = int(2 + sqrt(m));
  for (i = 0, x = 1 % m; i < 50; ++i) {
    if (x == r) return i;
    x = int64(x) * a % m;
  }
  static bool init = false;
  static std::vector<uint32> u(1000003), v(1000003);
  static std::vector<uint32> uu(1000033), vv(1000033);
  if (!init) {
    init = true;
    std::vector<std::pair<int64, int64>> xs;
    xs.emplace_back(1, 0);
    for (i = 1, x = 1; i < at; ++i){ // Baby Step
      x = x * a % m;
      xs.emplace_back(x, i);
    }
    for (int i = 0; i < at; ++i) {
      u[xs[i].first % 1000003] = xs[i].first;
      v[xs[i].first % 1000003] = xs[i].second;
      uu[xs[i].first % 1000033] = xs[i].first;
      vv[xs[i].first % 1000033] = xs[i].second;
    }
  }
  for (int i = 0; i < at; ++i) {
    if (u[i] == r) return v[i];
  }
  g = m - 1;
  g = pow_mod(a, g - at % g, m);
  for (i = 1; i < at; ++i) { // Giant Step
    r = (uint64)r * g % m;
    int64 t = r % 1000003;
    if (t < 1000003 && u[t] == r) return c + i * at + v[t];
    t = r % 1000033;
    if (t < 1000033 && uu[t] == r) return c + i * at + vv[t];
  }
  return -1;
}

int main() {
  int64 p, e;
  scanf("%lld%lld", &p, &e);
  auto g = gcd(e, p - 1);
  auto r = primitive_root(p);
  int k;
  scanf("%d", &k);
  for (int i = 0; i < k; ++i) {
    int64 n;
    scanf("%lld", &n);
    auto c = log(r, n, p);
    if (c % g == 0) puts("TAK");
    else puts("NIE");
  }
  return 0;
}

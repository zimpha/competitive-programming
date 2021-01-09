#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>

using i64 = long long;

const int N = 1e5 + 10, mod = 998244353;
const long double pi = acosl(-1.0);

char s[N];
int n, r;

i64 pow_mod(i64 a, i64 n) {
  i64 r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % mod;
    a = a * a % mod;
  }
  return r;
}

// poly * (1 + x^w) % (x^n - 1)
void mul(std::vector<i64> &poly, int w, int n) {
  std::vector<i64> ret(poly);
  for (size_t i = 0; i < poly.size(); ++i) {
    int j = (i + w) % poly.size();
    ret[j] = (ret[j] + poly[i]) % mod;
  }
  poly.swap(ret);
}

void transfer(std::vector<i64> &poly, int n, bool inverse) {
  if (inverse) {
    i64 inv = pow_mod(n, mod - 2);
    for (auto &x: poly) x = x * inv % mod;
  }
  std::vector<long double> coef(n);
  for (int i = 0; i < n; ++i) {
    coef[i] = cosl(pi * 2 * i / n);
  }
  std::vector<i64> ret(n);
  for (int d = 1; d <= n; ++d) if (n % d == 0) {
    long double sum = 0;
    for (int i = 0; i < n; ++i) {
      sum += poly[i] * coef[d * i % n];
    }
    i64 sum_r = i64(floorl(sum + 0.5)) % mod;
    if (sum_r < 0) sum_r += mod;
    for (int i = d; i <= n; i += d) if (std::__gcd(i, n) == d) {
      ret[i % n] = sum_r;
    }
  }
  poly.swap(ret);
  if (inverse) {
    std::reverse(poly.begin() + 1, poly.end());
  }
}

int main() {
  scanf("%d%d%s", &n, &r, s);

  i64 nmod = 0, t_val = 0;
  for (int i = 0; s[i]; ++i) {
    t_val = t_val * 10 + s[i] - '0';
    if (t_val > n) t_val = n;
    nmod = (nmod * 10 + s[i] - '0') % (i64(mod - 1) * n);
  }
  i64 t_div = nmod / n, t_rem = nmod % n;

  std::vector<i64> poly(n); poly[0] = 1;
  for (int i = 0; i < n; ++i) mul(poly, i, n);

  transfer(poly, n, false);
  for (int d = 1; d <= n; ++d) if (n % d == 0) {
    i64 w = poly[d % n];
    if (w == 0 && t_val >= n) w = 0;
    else w = pow_mod(w, t_div);
    for (int i = d; i <= n; i += d) if (std::__gcd(i, n) == d) {
      poly[i % n] = w;
    }
  }
  transfer(poly, n, true);

  for (int i = 0; i < t_rem; ++i) mul(poly, i, n);
  printf("%lld\n", poly[r]);
  return 0;
}

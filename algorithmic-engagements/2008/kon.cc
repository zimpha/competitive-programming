#include <cmath>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <vector>
#include <functional>
#include <unordered_map>
#include <algorithm>

using int64 = long long;

const int mod = 999999599;
const int phi = 999999598;

template<typename T>
T gcd(T a, T b) {
  return !b ? a : gcd(b, a % b);
}

// return x, where ax = 1 (mod mod)
int64 mod_inv(int64 a, int64 mod) {
  if (gcd(a, mod) != 1) return -1;
  int64 b = mod, s = 1, t = 0;
  while (b) {
    int64 q = a / b;
    std::swap(a -= q * b, b);
    std::swap(s -= q * t, t);
  }
  return s < 0 ? s + mod : s;
}

int64 crt(int n, int64 *c, int64 *m) {
  int64 M = 1, ans = 0;
  for (int i = 0; i < n; ++i) M *= m[i];
  for (int i = 0; i < n; ++i) {
    int64 tm = M / m[i];
    assert(tm * m[i] == M);
    int64 inv = mod_inv(tm % m[i], m[i]);
    assert(inv * tm % m[i] == 1);
    ans = (ans + tm * inv % M * c[i] % M) % M;
  }
  return (ans + M) % M;
}

namespace fft {
  const int N = 1 << 15;
  struct Complex {
    double x , y;
    Complex () {x = y = 0;}
    Complex (double _x , double _y) {x = _x , y = _y;}
    Complex operator + (const Complex& r) const {
      return Complex(x + r.x , y + r.y);
    }
    Complex operator - (const Complex& r) const {
      return Complex(x - r.x , y - r.y);
    }
    Complex operator * (const double k) const {
      return Complex(x * k, y * k);
    }
    Complex operator / (const double k) const {
      return Complex(x / k, y / k);
    }
    Complex operator * (const Complex& r) const {
      return Complex(x * r.x - y * r.y , x * r.y + y * r.x);
    }
    int operator = (const int a) {
      *this = Complex(a , 0);
      return a;
    }
    Complex conj() const {
      return Complex(x, -y);
    }
  };
  const double pi = acos(-1.0);
  Complex w[N];
  int rev[N];
  void init(int L) {
    int n = 1 << L;
    for (int i = 0; i < n; ++i) {
      double ang = 2 * pi * i / n;
      w[i] = Complex(cos(ang) , sin(ang));
      rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (L - 1));
    }
  }
  void trans(Complex P[], int n, int oper) {
    for (int i = 0; i < n; ++i) {
      if (i < rev[i]) {
        std::swap(P[i], P[rev[i]]);
      }
    }
    for (int d = 0; (1 << d) < n; d++) {
      int m = 1 << d, m2 = m * 2, rm = n / m2;
      for (int i = 0; i < n; i += m2) {
        for (int j = 0; j < m; j++) {
          Complex &P1 = P[i + j + m], &P2 = P[i + j];
          Complex t = w[rm * j] * P1;
          P1 = P2 - t;
          P2 = P2 + t;
        }
      }
    }
    if (oper == -1) {
      for (int i = 0; i < n; ++i) {
        P[i] = P[i] / n;
      }
    }
  }
  Complex A[N] , B[N];
  std::vector<int64> conv(const std::vector<int> &a, const std::vector<int> &b) {
    int n = a.size(), m = b.size(), L = 0, s = 1;
    while (s <= n + m - 2) s <<= 1, ++L;
    init(L);
    for (int i = 0; i < s; ++i) {
      A[i] = i < n ? Complex(a[i], 0) : Complex();
      B[i] = i < m ? Complex(b[i], 0) : Complex();
    }
    trans(A, s, 1);
    trans(B, s, 1);
    for (int i = 0; i < s; ++i) {
      A[i] = A[i] * B[i];
    }
    for (int i = 0; i < s; ++i) {
      w[i] = w[i].conj();
    }
    trans(A, s, -1);
    std::vector<int64> res(n + m - 1);
    for (int i = 0; i < n + m - 1; ++i) {
      res[i] = (int64)(A[i].x + 0.5);
    }
    return res;
  }
}

int bell[10000], tmp[10000];

int64 solve(int64 n, int p) {
  if (n <= p) return bell[n];
  std::vector<int> d;
  for (; n; n /= p) {
    d.push_back(n % p);
  }
  for (size_t i = 1; i < d.size(); ++i) {
    for (int j = 1; j <= d[i]; ++j) {
      for (int k = 0; k < p; ++k) {
        tmp[k] = (bell[k] * i + bell[k + 1]) % p;
      }
      tmp[p] = (tmp[0] + tmp[1]) % p;
      memcpy(bell, tmp, sizeof(int) * (p + 1));
    }
  }
  return bell[d[0]];
}

void prepare(int64 n, int p) {
  std::vector<int> fac(p, 1), inv(p, 1);
  for (int i = 1; i < p; ++i) {
    fac[i] = i * fac[i - 1] % p;
    inv[i] = mod_inv(fac[i], p);
  }
  int u = std::min<int64>(n, p) + 1;
  memset(bell, 0, sizeof(bell[0]) * u);
  std::function<void(int, int)> divide = [&] (int l, int r) {
    if (l + 1 == r) {
      if (l == 0) bell[l] = 1;
      else bell[l] = bell[l] * fac[l - 1] % p;
      return;
    }
    int m = (l + r) >> 1;
    divide(l, m);
    std::vector<int> a(m - l), b(r - l);
    for (int i = 0; i < m - l; ++i) {
      a[i] = bell[i + l] * inv[i + l] % p;
    }
    for (int i = 0; i < r - l; ++i) {
      b[i] = inv[i];
    }
    auto c = fft::conv(a, b);
    assert(c.size() == a.size() + b.size() - 1);
    for (int i = m; i < r; ++i) {
      bell[i] = (bell[i] + c[i - l - 1]) % p;
    }
    divide(m, r);
  };

  divide(0, u);
}

int main() {
  int64 n, m;
  scanf("%lld%lld", &n, &m);
  int64 mods[4] = {2, 13, 5281, 7283};
  int64 res[4] = {0, 0, 0, 0};
  for (int i = 0; i < 4; ++i) {
    prepare(n, mods[i]);
    res[i] = solve(n, mods[i]);
  }
  n = crt(4, res, mods) + phi;
  int64 ret = 1;
  for (m %= mod; n; n >>= 1) {
    if (n & 1) ret = ret * m % mod;
    m = m * m % mod;
  }
  printf("%lld\n", ret);
  return 0;
}

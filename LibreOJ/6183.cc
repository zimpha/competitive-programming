#include <cstdio>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;

using int64 = long long;

const int MAXN = 1 << 18, p = 99991;
const int64 P1 = 786433, P2 = 1811939329, M = P1 * P2;

int64 pm(int64 a, int64 n, int64 m) {
  int64 r=1;
  for (;n;n>>=1,a=a*a%m) if (n&1) r=r*a%m;
  return r;
}

int64 pw[MAXN];
int a[MAXN], n, m;

#include <cmath>
#include <vector>
#include <algorithm>

namespace fft {
  const int N = 1 << 20, M = 31768;
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
  void init(int n) {
    int LN = __builtin_ctz(n);
    for (int i = 0 ; i < n ; ++ i) {
      double ang = 2 * pi * i / n;
      w[i] = Complex(cos(ang) , sin(ang));
      rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (LN - 1));
    }
  }
  void trans(Complex P[], int n, int oper) {
    for (int i = 0 ; i < n ; i ++) {
      if (i < rev[i]) {
        std::swap(P[i], P[rev[i]]);
      }
    }
    for (int d = 0; (1 << d) < n; d++) {
      int m = 1 << d, m2 = m * 2 , rm = n / m2;
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
  Complex A[N] , B[N] , C1[N] , C2[N];
  std::vector<int64> conv(const std::vector<int64> &a, const std::vector<int64> &b) {
    int n = a.size(), m = b.size(), s = 1;
    while (s <= n + m - 2) s <<= 1;
    init(s);
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
    for (int i = 0; i < res.size(); ++i) {
      res[i] = (int64)(A[i].x + 0.5) % p;
    }
    return res;
  }
}

std::vector<int64> solve(int l, int r) {
  if (l + 1 == r) return {1, pw[l]};
  int m = (l + r) >> 1;
  auto f = solve(l, m);
  auto g = solve(m, r);
  return fft::conv(f, g);
}

int main() {
  int64 u = 3, v = p - 1;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++ i) scanf("%d", a + i);
  int f0, f1;
  scanf("%d%d", &f0, &f1);
  int x = (f0 + f1) * pm(4, p - 2, p) % p;
  int y = (f0 * 3 - f1 + p) * pm(4, p - 2, p) % p;

  for (int i = 0; i < n; ++ i) pw[i] = pm(u, a[i], p);
  int64 ret = solve(0, n)[m] * x % p;
  for (int i = 0; i < n; ++ i) pw[i] = pm(v, a[i], p);
  ret += solve(0, n)[m] * y % p;
  ret %= p;
  printf("%lld\n", ret);
  return 0;
}

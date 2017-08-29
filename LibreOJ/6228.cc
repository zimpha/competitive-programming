#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>

using int64 = long long;

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
  std::vector<int64> conv(const std::vector<int> &a, const std::vector<int> &b) {
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
      res[i] = (int64)(A[i].x + 0.5);
    }
    return res;
  }
}

int main() {
  const int V = 1e5 + 10;
  int n;
  scanf("%d", &n);
  std::vector<int> cnt(V);
  for (int i = 0; i < n; ++i) {
    int x;
    scanf("%d", &x);
    cnt[x]++;
  }
  auto sum = fft::conv(cnt, cnt);
  for (size_t i = 0; i < sum.size() && i / 2 < V; ++i) {
    if (i & 1) sum[i] >>= 1;
    else sum[i] = (sum[i] - cnt[i >> 1]) / 2;
  }
  for (int i = V - 2; i >= 0; --i) {
    cnt[i] += cnt[i + 1];
  }
  int64 x = (int64)n * (n - 1) * (n - 2) / 6;
  int64 y = (int64)n * (n - 1) * (n - 2) / 6;
  for (int i = 0; i < V; ++i) x -= sum[i] * cnt[i];
  printf("%.6f\n", 1.0 * x / y);
  return 0;
}

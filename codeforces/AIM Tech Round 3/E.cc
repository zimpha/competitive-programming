#include <bits/stdc++.h>

const int K = 100000 + 10, N = 1500 + 10, M = 1e9 + 7;

template<int M>
struct Mint {
  int x;
  Mint(): x(0) { }
  Mint(int y) {
    x = y % M;
    if (x < 0) x += M;
  }
  Mint(long long y) {
    x = y % M;
    if (x < 0) x += M;
  }
  int get() const {return x;}
  bool operator==(const Mint &r) const {return x==r.x;}
  Mint &operator+=(const Mint &r) {if((x+=r.x)>=M) x-=M; return *this;}
  Mint &operator-=(const Mint &r) {if((x+=M-r.x)>=M) x-=M; return *this;}
  Mint &operator*=(const Mint &r) {x=(long long)x*r.x%M; return *this;}
  Mint &operator/=(const Mint &r) {x=(long long)x*r.inv().x%M; return *this;}
  Mint operator+(const Mint &r) const {return Mint(*this)+=r;}
  Mint operator-(const Mint &r) const {return Mint(*this)-=r;}
  Mint operator*(const Mint &r) const {return Mint(*this)*=r;}
  Mint operator/(const Mint &r) const {return Mint(*this)/=r;}
  Mint pow(int n) const {
    Mint res(1), tmp(x);
    for (; n; n >>= 1) {
      if (n & 1) res *= tmp;
      tmp = tmp * tmp;
    }
    return res;
  }
  Mint inv() const {
    int a = x, b = M, u = 1, v = 0;
    while(b) {
      int t = a / b;
      a -= t * b; std::swap(a, b);
      u -= t * v; std::swap(u, v);
    }
    if(u < 0) u += M;
    Mint res; res.x = (unsigned)u;
    return res;
  }
};

typedef Mint<M> mint;

mint fac[K], inv[K], pw[N];
mint f[N][N];

void run() {
  int n, m, a, b, k;
  std::cin >> n >> m;
  std::cin >> a >> b;
  std::cin >> k;
  fac[0] = inv[0] = 1;
  for (int i = 1; i <= k; ++i) {
    fac[i] = fac[i - 1] * i;
    inv[i] = fac[i].inv();
  }
  mint p = mint(a) / mint(b), q = mint(b - a) / mint(b);
  for (int i = 1; i <= m && i <= k + 1; ++i) {
    pw[i] = fac[k] * inv[i - 1] * inv[k - i + 1];
    pw[i] *= p.pow(i - 1) * q.pow(k - i + 1);
  }
  for (int i = 0; i <= m; ++i) f[0][i] = 0;
  f[0][m] = 1;
  mint sp[N], spf[N];
  for (int i = 1; i <= n; ++i) {
    f[i][0] = sp[0] = spf[0] = 0;
    for (int r = 1; r <= m; ++r) {
      sp[r] = pw[m - r + 1] + sp[r - 1];
      spf[r] = pw[m - r + 1] * f[i - 1][m - r] + spf[r - 1];
    }
    mint u(0), v(0), w(0), x(0), y(0);
    for (int j = 1; j <= m; ++j) {
      u += pw[j];
      v += pw[j] * sp[j - 1];
      w += pw[j] * f[i - 1][j - 1];
      x += pw[j] * f[i - 1][j - 1] * sp[j - 1];
      y += pw[j] * spf[j - 1];
      mint &r = f[i][j];
      r = f[i - 1][m] * sp[j] * u;
      r -= f[i - 1][m] * v;
      r -= sp[j] * w;
      r += x;
      r -= spf[j] * u;
      r += y;
    }
  }
  std::cout << f[n][m].get() << std::endl;
}

int main() {
  run();
  return 0;
}

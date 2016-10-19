#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>
using namespace boost::multiprecision;

typedef int256_t vll;

void exgcd(vll a, vll b, vll &g, vll &x, vll &y) {
  if (b == 0) x = 1, y = 0, g = a;
  else {
    exgcd(b, a % b, g, y, x);
    y -= x * (a / b);
  }
}

bool lineq(vll a, vll b, vll c, vll &x, vll &y) {
  vll g;
  exgcd(a, b, g, x, y);
  b /= g, a /= g, c /= g;
  x = (x % b * (c % b) % b + b) % b;
  y = (c - a * x) / b;
  return true;
}

const int N = 10000000;

int mp[N], p[N], m;

void sieve() {
  for (int i = 2; i < N; ++i) {
    if (!mp[i]) mp[i] = i, p[m++] = i;
    for (int j = 0; j < m && p[j] * i < N; ++j) {
      mp[i * p[j]] = p[j];
      if (i % p[j] == 0) break;
    }
  }
}

template<typename T>
T gcd(T a, T b) {
  return b != 0 ? gcd(b, a % b) : a;
}

inline void update(vll &x, vll y) {
  if (x == -1 || x > y) x = y;
}

bool is_prime(int n) {
  if (n < N) return mp[n] == n;
}

int get_q(long A, long B) {
  static int fac[100], sz;
  sz = 0;
  for (int n = A; n != 1; n /= mp[n]) fac[sz++] = mp[n];
  for (int n = B; n != 1; n /= mp[n]) fac[sz++] = mp[n];
  std::sort(fac, fac + sz);
  sz = std::unique(fac, fac + sz) - fac;
  int q = 2;
  for (int i = 0; i < sz; ++i) {
    if (fac[i] != p[i]) break;
    q = p[i + 1];
  }
  return q;
}

vll solve(int c, int n) {
  vll ret = 1ll << 60;
  for (int msk = 0; msk < (1 << n); ++msk) {
    vll a = 1, b = 1;
    int ca = 0, cb = 0;
    for (int i = 0; i < n; ++i) {
      if (msk >> i & 1) a *= p[i], ++ca;
      else b *= p[i], ++cb;
    }
    vll x, y;
    lineq(a, -b, c, x, y);
    while (y >= 0) y -= a, x -= b;
    while (y < 0) y += a, x += b;
    for (int i = 0; i < 1000; ++i) {
      if (gcd(x, y) != 1) continue;
      vll A = a * x;
      if (A > 1ll << 60) break;
      ret = std::min(ret, A);
      x += b, y += a;
      break;
    }
  }
  return ret;
}

vll run(int n) {
  std::vector<vll> V(n + 1, -1);
  for (int i = 0; i < 20; ++i) {
    int q = p[i];
    std::cout << "start: " << q << std::endl;
    for (int j = 0; p[j] < q * q && p[j] <= n; ++j) {
      if (V[p[j]] == -1) {
        update(V[p[j]], solve(p[j], i));
      }
    }
  }
  for (int A = 1; A <= n; ++A) {
    for (int B = 1; A + B <= n && B <= A; ++B) {
      if (gcd(A, B) != 1) continue;
      if (!is_prime(A + B)) continue;
      int q = get_q(A, B);
      if (A + B < q * q) update(V[A + B], A);
    }
  }
  std::cout << "finished" << std::endl;
  vll ret = 0;
  for (int i = 2; i <= n; ++i) {
    if (mp[i] == i) {
      ret += V[i];
//      std::cout << i << ": " << V[i] << std::endl;
    }
  }
  return ret;
}

int main() {
  sieve();
  //std::cout << run(10) << std::endl;
  //std::cout << run(200) << std::endl;
  std::cout << run(3800) << std::endl;
  return 0;
}

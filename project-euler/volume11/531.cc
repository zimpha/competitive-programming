#include <bits/stdc++.h>

using LL = long long;

const int N = 1005000;

int phi[N];

void sieve() {
  for (int i = 1; i < N; ++i) phi[i] = i;
  for (int i = 2; i < N; ++i) if (phi[i] == i) {
    for (int j = i; j < N; j += i) {
      phi[j] = phi[j] / i * (i - 1);
    }
  }
}

inline LL add_mod(LL x, LL y) {
  return (x % y + y) % y;
}

void exgcd(LL a, LL b, LL &g, LL &x, LL &y) {
  if (!b) x = 1, y = 0, g = a;
  else {
    exgcd(b, a % b, g, y, x);
    y -= x * (a / b);
  }
}

LL g(LL a, LL n, LL b, LL m) {
  LL g, x, y;
  exgcd(n, m, g, x, y);
  if ((b - a) % g) return 0;
  LL res = add_mod((b - a) / g * x, m / g);
  res = add_mod(a + n * res, n / g * m);
  return res;
}

LL run(int l, int r) {
  LL ret = 0;
  for (int n = l; n < r; ++n) {
    for (int m = n + 1; m < r; ++m) {
      ret += g(phi[n], n, phi[m], m);
    }
  }
  return ret;
}

int main() {
  sieve();
  std::cout << g(2, 4, 4, 6) << std::endl;
  std::cout << g(3, 4, 4, 6) << std::endl;
  std::cout << run(1000000, 1005000) << std::endl;
  return 0;
}

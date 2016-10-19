#include <bits/stdc++.h>
using LL = long long;

const int M = 999999017, N = 10000000;
const int i2 = 499999509, i4 = 749999263, i12 = 583332760;

int f[N], phi[N];

void sieve() {
  for (int i = 0; i < N; ++i) phi[i] = i;
  for (int i = 2; i < N; ++i) if (phi[i] == i) {
    for (int j = i; j < N; j += i) phi[j] = phi[j] / i * (i - 1);
  }
  f[1] = 1;
  for (int i = 2; i < N; ++i) {
    f[i] = (f[i - 1] + 1ll * i * phi[i] / 2) % M;
  }
}

inline LL sum(LL n) {
  n %= M;
  return n * (n + 1) % M * (i4 + i12 * (n * 2 + 1) % M) % M;
}

inline LL ap(LL n) {
  n %= M;
  return n * (n + 1) % M * i2 % M;
}

std::map<LL, int> cache;

LL T(LL n) {
  if (n < N) return f[n];
  if (cache.count(n)) return cache[n];
  LL ret = sum(n);
  for (LL g = 2, h; g <= n; g = h + 1) {
    h = n / (n / g);
    ret -= T(n / g) * (ap(h) - ap(g - 1)) % M;
    ret %= M;
    if (ret < 0) ret += M;
  }
  return cache[n] = ret;
}

LL S(LL n) {
  LL ret = 0;
  for (LL i = 1, j; i <= n; i = j + 1) {
    j = n / (n / i);
    ret += (n / j) * (T(j) - T(i - 1)) % M;
  }
  return ret % M;
}

int main() {
  sieve();
  assert(S(100) == 122726);
  std::cout << S(99999999019ll) << std::endl;
  return 0;
}

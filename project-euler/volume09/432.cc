#include <map>
#include <cstring>
#include <iostream>

using int64 = long long;
using int128 = __int128;

const int mod = 1e9, N = 1000000;

int64 mp[N], phi[N];
int64 sp[N], lp[N];

void sieve() {
  for (int i = 0; i < N; ++i) phi[i] = i;
  for (int i = 2; i < N; ++i) {
    if (phi[i] != i) continue;
    for (int j = i; j < N; j += i) {
      if (!mp[j]) mp[j] = i;
      phi[j] = phi[j] / i * (i - 1);
    }
  }
  for (int i = 1; i < N; ++i) {
    sp[i] = (sp[i - 1] + phi[i]) % mod;
  }
}

int64 sum_phi(int64 n, int64 m) {
  if (n < N) return sp[n];
  int v = m / n;
  if (lp[v] != -1) return lp[v];
  int64 &ret = lp[v];
  ret = (int128)n * (n + 1) / 2 % mod;
  for (int64 i = 2, j; i <= n; i = j + 1) {
    j = n / (n / i);
    ret -= (j - i + 1) * sum_phi(n / i, m) % mod;
  }
  ret %= mod; ret += mod; ret %= mod;
  return ret;
}

int64 S(int64 n, int64 m, int64 u) {
  if (m == 0) return 0;
  if (m == 1) return phi[n];
  if (n == 1) return sum_phi(m, u);
  int p = mp[n];
  return ((p - 1) * S(n / p, m, u) + S(n, m / p, u)) % mod;
}

int main() {
  sieve();
  memset(lp, -1, sizeof(lp));
  std::cout << S(510510, 1000000, 1000000) << std::endl;
  memset(lp, -1, sizeof(lp));
  std::cout << S(510510, 100000000000ll, 100000000000ll) << std::endl;
  return 0;
}

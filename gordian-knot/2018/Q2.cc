#include <cstdio>

using int64 = long long;

const int N = 100000000, mod = 1e9 + 7;

int phi[N], p[10000], pc;

int main() {
  for (int i = 2; i < N; ++i) {
    if (!phi[i]) {
      phi[i] = i - 1;
      if (1ll * i * i < N) p[pc++] = i;
    }
    for (int j = 0, u = (N - 1) / i; j < pc && p[j] <= u; ++j) {
      if (i % p[j] == 0) {
        phi[i * p[j]] = phi[i] * p[j];
        break;
      } else {
        phi[i * p[j]] = phi[i] * (p[j] - 1);
      }
    }
  }
  int64 ret = 0, now = 0;
  for (int i = 1; i <= 100000000 / 2; ++i) {
    int64 total = (int64(i) * i * 4 + i * 4) % mod;
    now += phi[i] * 8;
    now %= mod;
    ret += (total - now - 8) % mod;
  }
  ret %= mod;
  ret += mod;
  ret %= mod;
  printf("%lld\n", ret);
  return 0;
}

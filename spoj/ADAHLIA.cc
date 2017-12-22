#include <cstdio>
#include <cstring>
#include <cassert>

using int64 = long long;
using int128 = __int128;

constexpr int U = 1 << 16, N = 4e7 + 10;

int64 X[N], Y[N];
int cx[U], cy[U], cz[U], cw[U];

inline int64 mul_mod(int64 a, int64 b, int64 mod) {
  if (mod < int(1e9)) return a * b % mod;
  int64 k = (int64)((long double)a * b / mod);
  int64 res = a * b - k * mod;
  res %= mod;
  if (res < 0) res += mod;
  return res;
}

int main() {
  int n;
  int64 a, b, mod;
  scanf("%d%lld%lld%lld%lld", &n, &a, &b, &mod, &X[0]);
  a %= mod, b %= mod;
  memset(cx, 0, sizeof(cx));
  memset(cy, 0, sizeof(cy));
  memset(cz, 0, sizeof(cz));
  for (int i = 1; i < n; ++i) {
    //X[i] = mul_mod(X[i - 1], a, mod) + b;
    //if (X[i] >= mod) X[i] -= mod;
    X[i] = ((int128)X[i - 1] * a + b) % mod;
  }
  for  (int i = 0; i < n; ++i) {
    cx[X[i] & (U - 1)]++;
    cy[X[i] >> 16 & (U - 1)]++;
    cz[X[i] >> 32 & (U - 1)]++;
    cw[X[i] >> 48]++;
  }
  for (int i = 1; i < U; ++i) {
    cy[i] += cy[i - 1];
    cx[i] += cx[i - 1];
    cz[i] += cz[i - 1];
    cw[i] += cw[i - 1];
  }
  for (int i = n - 1; i >= 0; --i) {
    Y[--cx[X[i] & (U - 1)]] = X[i];
  }
  for (int i = n - 1; i >= 0; --i) {
    X[--cy[Y[i] >> 16 & (U - 1)]] = Y[i];
  }
  for (int i = n - 1; i >= 0; --i) {
    Y[--cz[X[i] >> 32 & (U - 1)]] = X[i];
  }
  for (int i = n - 1; i >= 0; --i) {
    X[--cw[Y[i] >> 48]] = Y[i];
  }
  int64 ret = 0;
  for (int i = 1; i < n; ++i) {
    if (X[i] - X[i - 1] > ret) ret = X[i] - X[i - 1];
  }
  printf("%lld\n", ret);
  return 0;
}

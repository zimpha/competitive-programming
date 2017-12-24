#include <cstdio> 

using int64 = long long;

const int N = 1e6 + 10, mod = 5e8 + 3;

int64 fact[N], inv[N], ifact[N];

int64 binom(int a, int b) {
  if (b > a) return 0;
  return fact[a] * ifact[b] % mod * ifact[a - b] % mod;
}

void prepare() {
  fact[0] = ifact[0] = inv[0] = 1;
  fact[1] = ifact[1] = inv[1] = 1;
  for (int i = 2; i < N; ++i) {
    fact[i] = i * fact[i - 1] % mod;
    inv[i] = (mod - mod / i) * inv[mod % i] % mod;
    ifact[i] = inv[i] * ifact[i - 1] % mod;
  }
}

int main() {
  prepare();
  int n, x, y;
  scanf("%d%d%d", &n, &x, &y);
  if (x < 0) x = -x;
  if (y < 0) y = -y;

  int64 ret = 0;
  for (int h = x; h <= n; h += 2) {
    int v = n - h;
    if (v < y || (v - y) % 2 == 1) continue;
    ret += binom(h, (h - x) / 2) * binom(v, (v - y) / 2) % mod * binom(n, h) % mod;
  }
  printf("%lld\n", ret % mod);
  return 0;
}

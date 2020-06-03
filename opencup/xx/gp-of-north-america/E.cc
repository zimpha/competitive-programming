#include <cstdio>

using int64 = long long;

int n, m, mod;
int dp[2][13][1 << 12];

void add(int &x, int y) {
  if ((x += y) >= mod) x -= mod;
}

int64 pow_mod(int64 a, int64 n) {
  int64 r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % mod;
    a = a * a % mod;
  }
  return r;
}

int main() {
  scanf("%d%d%d", &n, &m, &mod);
  if (n % 2 == 1 && m % 2 == 1) { puts("1"); return 0; }
  if (n % 2 == 0 && m % 2 == 1) { printf("%lld\n", pow_mod(n / 2 + 1, m / 2)); return 0; }
  if (n % 2 == 1 && m % 2 == 0) { printf("%lld\n", pow_mod(m / 2 + 1, n / 2)); return 0; }
  n /= 2, m /= 2;
  return 0;
}

#include <cstdio>

using int64 = long long;

const int mod = 1e9 + 7;

int64 count(int64 n, int64 a, int64 b, int64 m) {
  if (b == 0) return n * (a / m) % mod;
  if (a >= m) return (n * (a / m) + count(n, a % m, b, m)) % mod;
  if (b >= m) return ((n - 1) * n / 2 % mod * (b / m) + count(n, a, b % m, m)) % mod;
  return count((a + b * n) / m, (a + b * n) % m, m, b);
}

int main() {
  int64 n, a, c;
  scanf("%lld%lld%lld", &n, &a, &c);
  printf("%lld\n", count(n + 1, 0, a, c));
  return 0;
}

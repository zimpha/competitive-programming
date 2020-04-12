#include <cstdio>
#include <vector>

using int64 = long long;

int main() {
  int n, mod;
  scanf("%d%d", &n, &mod);
  std::vector<int64> a(n), b(n), c(n), d(n);
  a[0] = 1;
  for (int i = 1; i < n; ++i) {
    for (int j = 0; j < i; ++j) {
      b[i] += a[j] * a[i - 1 - j] % mod;
      c[i] += b[j] * a[i - 1 - j] % mod;
      d[i] += (d[j] + c[j]) * a[i - 1 - j] % mod;
    }
    b[i] %= mod; c[i] %= mod; d[i] %= mod;
    a[i] = (b[i] + c[i] + d[i] * 2) % mod;
  }
  for (int i = 0; i < n; ++i) printf("%lld\n", a[i]);
  return 0;
}

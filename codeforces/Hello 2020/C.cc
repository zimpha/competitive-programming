#include <cstdio>
#include <vector>

using int64 = long long;

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  std::vector<int64> fac(n + 1, 1);
  for (int i = 1; i <= n; ++i) fac[i] = fac[i - 1] * i % m;
  int64 ret = 0;
  for (int i = 1; i <= n; ++i) {
    ret += fac[i] * (n - i + 1) % m * fac[n - i] % m * (n - i + 1) % m;
  }
  printf("%lld\n", ret % m);
  return 0;
}

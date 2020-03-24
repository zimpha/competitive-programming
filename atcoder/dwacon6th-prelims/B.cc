#include <cstdio>
#include <vector>

using int64 = long long;

const int mod = 1e9 + 7;

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> x(n), inv(n, 1);
  for (int i = 0; i < n; ++i) scanf("%d", &x[i]);
  for (int i = 2; i < n; ++i) {
    inv[i] = int64(mod - mod / i) * inv[mod % i] % mod;
  }
  int64 ret = 0, sum = 0;
  for (int i = 0; i + 1 < n; ++i) {
    sum += inv[i + 1];
    sum %= mod;
    ret += (x[i + 1] - x[i]) * sum % mod;
  }
  ret %= mod;
  for (int i = 1; i < n; ++i) ret = ret * i % mod;
  printf("%lld\n", ret);
  return 0;
}

#include <cstdio>
#include <cmath>
#include <vector>

using int64 = long long;
using int128 = long long;

const int mod = 1e9 + 7, i24 = 41666667;

int main() {
  int n;
  scanf("%d", &n);
  const int s = sqrt(n);
  std::vector<int64> ssum(s + 1), lsum(s + 1);
  auto pow_sum = [] (int128 n) {
    return n * (n + 1) * (n * 2 + 1) / 6 % mod;
  };
  for (int i = 1; i <= s; ++i) {
    ssum[i] = (int64)i * (i + 1) * (i + 2) * (i * 3 + 1) % mod * i24 % mod;
    for (int x = 2, y; x <= i; x = y + 1) {
      y = i / (i / x);
      ssum[i] -= ssum[i / x] * (pow_sum(y) - pow_sum(x - 1)) % mod;
      ssum[i] %= mod;
    }
    ssum[i] += mod; ssum[i] %= mod;
  }
  for (int i = s; i >= 1; --i) {
    int u = n / i;
    lsum[i] = (int64)u * (u + 1) % mod * (u + 2) % mod * (u * 3 + 1) % mod * i24 % mod;
    for (int x = 2, y; x <= u; x = y + 1) {
      y = u / (u / x);
      int v = u / x;
      lsum[i] -= (v <= s ? ssum[v] : lsum[n / v]) * (pow_sum(y) - pow_sum(x - 1)) % mod;
      lsum[i] %= mod;
    }
    lsum[i] += mod; lsum[i] %= mod;
  }
  int64 ret = 0;
  for (int i = 1, j; i <= n; i = j + 1) {
    j = n / (n / i);
    int v = n / i;
    ret += (v <= s ? ssum[v] : lsum[n / v]) * (j - i + 1) % mod;
    ret %= mod;
  }
  printf("%lld\n", ret);
  return 0;
}

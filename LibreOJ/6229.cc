#include <cstdio>
#include <cmath>
#include <vector>
#include <functional>

using int64 = long long;
using int128 = __int128;

const int mod = 1e9 + 7, i24 = 41666667;

int main() {
  int n, m = 0;
  scanf("%d", &n);
  const int s = std::max((int)sqrt(n), 1000000);
  std::vector<int64> ssum(s + 1), lsum(s + 1, -1);
  std::vector<int> p(s + 1);
  ssum[1] = 1;
  for (int i = 2; i <= s; ++i) {
    if (!p[i]) p[m++] = i, ssum[i] = i - 1;
    for (int j = 0; j < m && p[j] <= s / i; ++j) {
      p[i * p[j]] = 1;
      if (i % p[j]) ssum[i * p[j]] = ssum[i] * (p[j] - 1);
      else {
        ssum[i * p[j]] = ssum[i] * p[j];
        break;
      }
    }
  }
  for (int i = 2; i <= s; ++i) {
    ssum[i] = ssum[i] * i / 2 * i % mod;
    ssum[i] = (ssum[i] + ssum[i - 1]) % mod;
  }
  auto pow_sum = [] (int128 n) {
    return n * (n + 1) * (n * 2 + 1) / 6 % mod;
  };
  std::function<int64(int64)> solve = [&](int64 u) {
    if (u <= s) return ssum[u];
    int i = n / u;
    if (lsum[i] != -1) return lsum[i];
    lsum[i] = u * (u + 1) % mod * (u + 2) % mod * (u * 3 + 1) % mod * i24 % mod;
    for (int x = 2, y; x <= u; x = y + 1) {
      y = u / (u / x);
      lsum[i] -= solve(u / x) * (pow_sum(y) - pow_sum(x - 1)) % mod;
      lsum[i] %= mod;
    }
    lsum[i] += mod; lsum[i] %= mod;
    return lsum[i];
  };
  int64 ret = 0;
  for (int i = 1, j; i <= n; i = j + 1) {
    j = n / (n / i);
    ret += solve(n / i) * (j - i + 1) % mod;
    ret %= mod;
  }
  printf("%lld\n", ret);
  return 0;
}

#include <cstdio>
#include <vector>

using int64 = long long;

const int mod = 1e9 + 7, N = 1e5 + 10;

int64 pow_mod(int64 a, int64 n, int64 mod) {
  int64 r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % mod;
    a = a * a % mod;
  }
  return r;
}

int64 inv(int64 x) {
  return pow_mod(x, mod - 2, mod);
}

int64 dp[N];

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> a(n);
  int64 sum = 0;
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
    sum += a[i];
  }
  dp[0] = 0;
  dp[1] = (sum - 1) * (sum - 1) % mod * inv(sum) % mod;
  for (int i = 1; i + 1 < N; ++i) {
    dp[i + 1] = (2 * dp[i] - dp[i - 1] - (sum - 1) * inv(sum - i)) % mod;
    dp[i + 1] %= mod;
    dp[i + 1] = (dp[i + 1] + mod) % mod;
  }
  int64 ret = 0;
  for (auto &&x: a) {
    ret = (ret + dp[x]) % mod;
  }
  printf("%lld\n", ret);
  return 0;
}
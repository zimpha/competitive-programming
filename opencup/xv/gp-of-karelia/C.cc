#include <cstdio>
#include <cstring>
#include <vector>

using int64 = long long;

const int N = 3000 + 10, mod = 1e9 + 7;

int64 dp[N], size[N], fac[N], ifac[N];

int binom(int n, int m) {
  if (n < m || n < 0 || m < 0) return 0;
  return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}

int main() {
  fac[0] = fac[1] = ifac[0] = ifac[1] = 1;
  for (int i = 2; i < N; ++i) {
    fac[i] = i * fac[i - 1] % mod;
    ifac[i] = (mod - mod / i) * ifac[mod % i] % mod;
  }
  for (int i = 2; i < N; ++i) {
    ifac[i] = ifac[i - 1] * ifac[i] % mod;
  }
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, d;
    scanf("%d%d", &n, &d);
    std::vector<int> perm(n);
    for (int i = 0; i < n; ++i) {
      scanf("%d", &perm[i]);
      --perm[i];
    }
    for (int i = 0; i < n; ++i) dp[i] = 1, size[i] = 0;
    for (int i = n - 1; i >= 0; --i) {
      size[i] += 1;
      if (!i) break;
      int p = (i - 1) / d;
      size[p] += size[i];
      dp[p] = dp[p] * dp[i] % mod * binom(size[p], size[i]) % mod;
    }

    std::vector<int> cnt(n + 1);
    int64 ret = dp[0];
    for (int i = n - 1; i >= 0; --i) {
      int64 ways = dp[i];
      std::vector<int> limits(n, -1);
      limits[perm[i]] = size[i];
      for (int j = perm[i]; j >= 0; --j) cnt[j]++;
      for (int j = i / d; j < i && j * d + 1 < n; ++j) {
        // [j * d + 1, j * d + d]
        int sum = 0;
        for (int k = std::max(j * d, i) + 1; k <= j * d + d && k < n; ++k) {
          sum += size[k];
          ways = ways * dp[k] % mod * binom(sum, size[k]) % mod;
        }
        limits[perm[j]] = sum;
      }
      int sum = 0;
      for (int j = n - 1; j >= 0; --j) if (limits[j] != -1) {
        ways = ways * binom(cnt[j + 1] - sum, limits[j]) % mod;
        sum += limits[j];
      }
      ret -= ways % mod;
    }
    ret %= mod; ret += mod; ret %= mod;
    printf("%lld\n", ret);
  }
  return 0;
}

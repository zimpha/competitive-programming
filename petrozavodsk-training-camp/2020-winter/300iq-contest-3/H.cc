#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

const int N = 5e3 + 10;
const int mod = 998244353;

using int64 = long long;

int dp[2][N], inv[N];

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
  int n;
  scanf("%d", &n);
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
    inv[i + 1] = pow_mod(i + 1, mod - 2);
  }
  std::sort(a.begin(), a.end());
  memset(dp, 0, sizeof(dp));
  int64 ret = 0;
  int now = 0, next = 1;
  dp[0][0] = 1;
  for (int i = 0; i < n; ++i) {
    int delta = i ? a[i] - a[i - 1] : a[i];
    memset(dp[next], 0, sizeof(dp[next]));
    for (int j = 0; j + delta <= n; ++j) if (dp[now][j]) {
      int64 binom = 1;
      for (int k = 0; k <= delta; ++k) {
        add(dp[next][j + k], dp[now][j] * binom % mod);
        binom = binom * (delta - k) % mod * inv[k + 1] % mod;
      }
    }
    std::swap(now, next);
    memset(dp[next], 0, sizeof(dp[next]));
    for (int j = 0; j <= n; ++j) if (dp[now][j]) {
      if (j == 1) ret += dp[now][j];
      if (j) add(dp[next][j - 1], (int64)j * (j - 1) * dp[now][j] % mod);
      add(dp[next][j], dp[now][j]);
    }
    std::swap(now, next);
  }
  for (auto &x: a) ret -= x;
  ret %= mod; ret += mod; ret %= mod;
  printf("%lld\n", ret * inv[2] % mod);
  return 0;
}

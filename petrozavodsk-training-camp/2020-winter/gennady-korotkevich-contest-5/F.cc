#include <cstdio>
#include <vector>
#include <algorithm>

using int64 = long long;

const int mod = 998244353;

int main() {
  int n, m;
  scanf("%d%d", &n, &m);

  std::vector<int64> fac(n * 2 + 1), ifac(n * 2 + 1), inv(n * 2 + 1);
  fac[0] = fac[1] = ifac[0] = ifac[1] = inv[1] = 1;
  for (int i = 2; i <= n * 2; ++i) {
    fac[i] = fac[i - 1] * i % mod;
    inv[i] = (mod - mod / i) * inv[mod % i] % mod;
    ifac[i] = ifac[i - 1] * inv[i] % mod;
  }
  std::vector<int64> pw(n * 2 + 1, 1);
  for (int i = 1; i <= n * 2; ++i) {
    pw[i] = pw[i - 1] * inv[2] % mod;
  }

  auto binom = [&](int n, int m) ->int64 {
    if (n < 0 || m < 0 || n < m) return 0;
    else return fac[n] * ifac[n - m] % mod * ifac[m] % mod;
  };

  std::vector<std::vector<int>> a(m);
  std::vector<std::pair<int, int>> size(m);
  for (int i = 0; i < m; ++i) {
    scanf("%d", &size[i].first);
    size[i].second = i;
    a[i].resize(size[i].first);
    for (int j = 0; j < size[i].first; ++j) {
      scanf("%d", &a[i][j]);
    }
  }
  std::sort(size.begin(), size.end());
  std::vector<int64> sum(n * 2 + 1), pre(n * 2 + 1);
  for (int i = 0; i <= n * 2; ++i) {
    if (i) sum[i] = sum[i - 1];
    sum[i] += binom(i, n - 1) * pw[i] % mod;
    if (sum[i] >= mod) sum[i] -= mod;
  }
  std::vector<int64> ret(m);
  for (int i = 0, j = 0; i < m; i = j) {
    int k = size[i].first;
    for (int s = 0; s <= n * 2; ++s) {
      if (s) pre[s] = pre[s - 1];
      else pre[s] = 0;
      pre[s] += binom(s, n - k - 1) * pw[s] % mod;
      if (pre[s] >= mod) pre[s] -= mod;
    }
    for (j = i; j < m && k == size[j].first; ++j) {
      int e = size[j].second;
      if (a[e].back() != n * 2) {
        ret[e] = binom(a[e].back() - k, n - k) * pw[a[e].back()] % mod;
      }
      int prev = 0;
      for (int s = 0; s < k; ++s) {
        int64 w = mod;
        if (a[e][s] - 2 >= s) w += sum[a[e][s] - 2 - s];
        if (prev >= s + 1) w -= sum[prev - s - 1];
        ret[e] += pw[s + 1] * w % mod;
        prev = a[e][s];
      }
      if (prev + 1 <= n * 2 - 1) {
        int64 w = mod;
        if (n * 2 - 2 >= k) w += sum[n * 2 - 2 - k];
        if (prev >= k + 1) w -= sum[prev - k - 1];
        ret[e] += pw[k + 1] * w % mod;
      }
      if (2 * n - 1 >= a[e].back() + 1) {
        ret[e] += pw[k + 1] * (pre[2 * n - 1 - k - 1] - (a[e].back() >= k + 1 ? pre[a[e].back() - k - 1] : 0) + mod) % mod;
      }
    }
  }
  for (int i = 0; i < m; ++i) printf("%lld\n", ret[i] * 2 % mod);
  return 0;
}

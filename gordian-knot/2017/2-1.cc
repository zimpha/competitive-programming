#include <bits/stdc++.h>

long pow_mod(long a, long n, long m) {
  long r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % m;
    a = a * a % m;
  }
  return r;
}

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> mp(n + 1, 0);
  for (int i = 2; i <= n; ++i) if (!mp[i]) {
    for (int j = i; j <= n; j += i) mp[j] = i;
  }
  std::vector<long> mx(n + 1, 0);
  for (int i = 2; i <= n; ++i) {
    static int pl[100], cnt[100], m;
    m = 0;
    for (int j = i; j != 1; j /= mp[j]) {
      if (!m || pl[m - 1] != mp[j]) pl[m] = mp[j], cnt[m++] = 1;
      else cnt[m - 1]++;
    }
    for (int j = 0; j < m; ++j) {
      mx[pl[j]] = std::max<long>(mx[pl[j]], cnt[j]);
    }
  }
  const int mod = 1e9 + 7;
  long long ret = 1;
  for (int i = 2; i <= n; ++i) if (mp[i] == i) {
    int c = 0;
    for (long p = i; p <= n; p *= i) c += 1;
    //if (mp[i] == i) ret = ret * pow_mod(i, mx[i], mod) % mod;
    ret = (c + 1) % mod * ret % mod;
  }
  std::cout << ret << std::endl;
  return 0;
}

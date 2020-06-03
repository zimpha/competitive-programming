#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>

using int64 = long long;

const int mod = 1e9 + 7;

int64 pow_mod(int64 a, int64 n) {
  int64 r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % mod;
    a = a * a % mod;
  }
  return r;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    std::vector<int> a;
    std::map<int, int> mp;
    for (int i = 0; i < n; ++i) {
      int x;
      scanf("%d", &x);
      mp[x]++;
    }
    for (auto &&e: mp) {
      a.emplace_back(e.second);
    }
    std::vector<int64> fac(n + 1, 1), ifac(n + 1, 1);
    for (int i = 1; i <= n; ++i) {
      fac[i] = i * fac[i - 1] % mod;
      ifac[i] = pow_mod(fac[i], mod - 2);
    }
    int64 ret = 1;
    bool has = 0;
    for (auto &&x: a) {
      int cnt = 0, y = x;
      if (has) --y, ++cnt;
      if (y & 1) has = 1, ++cnt;
      else has = 0;
      y /= 2;
      if (cnt == 1) ret = x * ret % mod;
      else if (cnt == 2) ret = (int64)x * (x - 1) % mod * ret % mod;
      for (int i = 1; i <= y; ++i) {
        ret = (int64)i * (i * 2 - 1) % mod * ret % mod;
      }
      ret = ret * ifac[y] % mod;
    }
    printf("%lld\n", ret);
  }
  return 0;
}

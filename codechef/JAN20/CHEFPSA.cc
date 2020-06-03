#include <cstdio>
#include <vector>
#include <map>

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
    std::vector<int64> fac(n + 1, 1), ifac(n + 1, 1);
    for (int i = 1; i <= n; ++i) {
      fac[i] = i * fac[i - 1] % mod;
      ifac[i] = pow_mod(fac[i], mod - 2);
    }
    std::map<int64, int> cnt;
    int64 sum = 0;
    for (int i = 0, x; i < n * 2; ++i) {
      scanf("%d", &x);
      sum += x;
      cnt[x]++;
    }
    if (sum % (n + 1)) {
      puts("0");
      continue;
    }
    sum /= n + 1;
    std::vector<std::pair<int64, int>> gx, gy;
    if (!cnt.count(sum) || cnt[sum] < 2) {
      puts("0");
      continue;
    }
    cnt[sum] -= 2;
    if (cnt[sum] == 0) cnt.erase(sum);
    bool valid = true;
    for (auto &e: cnt) {
      valid &= cnt.count(sum - e.first);
      if (!valid) break;
      if (e.first <= sum - e.first) {
        gx.emplace_back(e.first, e.second);
        gy.emplace_back(sum - e.first, cnt[sum - e.first]);
        valid &= gx.back().second == gy.back().second;
        if (e.first == sum - e.first) valid &= e.second % 2 == 0;
      }
      if (!valid) break;
    }
    if (!valid) {
      puts("0");
      continue;
    }
    int64 ret = fac[n - 1];
    for (size_t i = 0; i < gx.size(); ++i) {
      //printf("%lld %d %lld %d\n", gx[i].first, gx[i].second, gy[i].first, gy[i].second);
      if (gx.at(i).first == gy.at(i).first) {
        ret = ret * ifac[gx[i].second / 2] % mod;
      } else {
        int64 sum = 0;
        for (int j = 0; j <= gx[i].second; ++j) sum += ifac[j] * ifac[gx[i].second - j] % mod;
        ret = ret * (sum % mod) % mod;
      }
    }
    printf("%lld\n", ret);
  }
  return 0;
}

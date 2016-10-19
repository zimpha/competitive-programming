#include <bits/stdc++.h>

using LL = long long;

LL cnt[100];

LL solve(LL k, LL n, LL mul) {
  if (n == 0) return 0;
  LL sz = 1ll << (k - 1);
  if (n == sz) return mul * cnt[k - 1];
  if (n < sz) return solve(k - 1, n, mul);
  else return cnt[k - 1] * mul + solve(k - 1, n - sz, mul * 2);
}

LL run(LL n) {
  n = (n - 1) / 4;
  cnt[0] = 2;
  for (int i = 1; i < 100; ++i) cnt[i] = cnt[i - 1] * 3;
  LL ret = 1, now = 0, k;
  for (k = 0; ; ++k) {
    now += 1ll << k;
    ret += cnt[k];
    if (now > n) {
      ret -= cnt[k];
      now -= 1ll << k;
      break;
    }
  }
  n -= now;
  return ret + solve(k, n, 1);
}

int main() {
  std::cout << run(10) << std::endl;
  std::cout << run(29) << std::endl;
  std::cout << run(121) << std::endl;
  std::cout << run(1000000000000ll) << std::endl;
  return 0;
}

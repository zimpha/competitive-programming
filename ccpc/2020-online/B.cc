#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>

using i64 = long long;

i64 sub_mod(i64 x, i64 y, i64 mod) {
  x -= y;
  if (x < 0) x += mod;
  return x;
}

// return the sum of p^k for all p <= m, where m is in form floor(n / i)
// for m <= sqrt{n}, stored in ssum[m]; for m > sqrt{n} stored in lsum[n / m]
// note: if you need all correct value of ssum and lsum, please remove `mark`
// and make `delta` always be 1
i64 prime_count(i64 n, i64 k, i64 mod) {
  auto pow_sum = [](i64 n, i64 k, i64 mod) {
    i64 x = n, y = n + 1;
    if (x % 2 == 0) x /= 2;
    else y /= 2;
    return (x % mod) * (y % mod) % mod;
  };
  const i64 v = static_cast<i64>(sqrt(n));
  std::vector<i64> ssum(v + 1), lsum(v + 1);
  std::vector<bool> mark(v + 1);
  for (int i = 1; i <= v; ++i) {
    ssum[i] = pow_sum(i, k, mod) - 1;
    lsum[i] = pow_sum(n / i, k, mod) - 1;
  }
  for (i64 p = 2; p <= v; ++p) {
    if (ssum[p] == ssum[p - 1]) continue;
    i64 psum = ssum[p - 1], q = p * p, ed = std::min(v, n / q);
    i64 pk = p % mod;
    int delta = (p & 1) + 1;
    for (int i = 1; i <= ed; i += delta) if (!mark[i]) {
      i64 d = i * p;
      if (d <= v) {
        lsum[i] = sub_mod(lsum[i], sub_mod(lsum[d], psum, mod) * pk % mod, mod);
      } else {
        lsum[i] = sub_mod(lsum[i], sub_mod(ssum[n / d], psum, mod) * pk % mod, mod);
      }
    }
    for (i64 i = q; i <= ed; i += p * delta) mark[i] = true;
    for (i64 i = v; i >= q; --i) {
      ssum[i] = sub_mod(ssum[i], sub_mod(ssum[i / p], psum, mod) * pk % mod, mod);
    }
  }
  return lsum[1];
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    i64 n, mod;
    scanf("%lld%lld", &n, &mod);
    i64 sum = prime_count(n + 1, 1, mod) - 2;
    i64 x = n + 4, y = n - 1;
    if (x % 2 == 0) x /= 2;
    else y /= 2;
    sum += (x % mod) * (y % mod) % mod;
    sum %= mod; sum += mod;
    printf("%lld\n", sum % mod);
  }
  return 0;
}

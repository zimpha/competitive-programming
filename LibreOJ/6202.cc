#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>

using int64 = long long;
using int128 = __int128;

// return the sum of p^k for all p <= m, where m is in form floor(n / i)
// for m <= sqrt{n}, stored in ssum[m]; for m > sqrt{n} stored in lsum[n / m]
int128 prime_count(int64 n) {
  if (n < 2) return 0;
  const int64 v = static_cast<int64>(sqrt(n));
  std::vector<int128> ssum(v + 1), lsum(v + 1);
  std::vector<bool> mark(v + 1);
  for (int i = 1; i <= v; ++i) {
    ssum[i] = (int128)i * (i + 1) / 2 - 1;
    lsum[i] = (int128)(n / i) * (n / i + 1) / 2 - 1;
  }
  for (int64 p = 2; p <= v; ++p) {
    if (ssum[p] == ssum[p - 1]) continue;
    int128 psum = ssum[p - 1];
    int64 q = p * p, ed = std::min(v, n / q);
    for (int64 i = q; i <= v; i += q) {
      mark[i] = true;
    }
    for (int i = 1; i <= ed; ++i) {
      if (mark[i]) continue;
      int64 d = i * p;
      if (d <= v) {
        lsum[i] -= (lsum[d] - psum) * p;
      } else {
        lsum[i] -= (ssum[n / d] - psum) * p;
      }
    }
    for (int64 i = v; i >= q; --i) {
      ssum[i] -= (ssum[i / p] - psum) * p;
    }
  }
  return lsum[1];
}

int main() {
  int64 L, R;
  scanf("%lld%lld", &L, &R);
  int128 res = prime_count(R) - prime_count(L - 1);
  int64 base = 1000000000000000000ll;
  if (res > base) printf("%lld%018lld\n", int64(res / base), int64(res % base));
  else printf("%lld\n", (int64)res);
  return 0;
}
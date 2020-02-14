#include <cmath>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using int64 = long long;
using int128 = __int128_t;

const int mod = 998244353;

bool is_prime(int64 n) {
  if (n <= 1) return false;
  if (n <= 3) return true;
  if (n % 2 == 0) return false;
  for (int64 i = 3; i * i <= n; i += 2) {
    if (n % i == 0) return false;
  }
  return true;
}

int64 count(int64 n, int64 k) {
  if (n <= 1 || !is_prime(k)) return 0;
  const int64 v = static_cast<int64>(sqrt(n));
  std::vector<int128> ssum(v + 1), lsum(v + 1);
  std::vector<int64> scnt(v + 1), lcnt(v + 1);
  std::vector<bool> mark(v + 1);
  auto sum = [&](int64 n) {
    int64 x = n, y = n + 1;
    if (x & 1) y >>= 1;
    else x >>= 1;
    return (int128)x * y;
  };
  for (int64 i = 1; i <= v; ++i) {
    ssum[i] = sum(i) - 1;
    scnt[i] = i - 1;
    lsum[i] = sum(n / i) - 1;
    lcnt[i] = n / i - 1;
  }
  int128 ret = 0;
  for (int64 p = 2; p <= v; ++p) {
    if (scnt[p] == scnt[p - 1]) continue;
    int128 psum = ssum[p - 1];
    int64 pcnt = scnt[p - 1];
    int64 q = p * p, ed = std::min(v, n / q);
    if (p == k) ret += lsum[1];
    assert(ret >= 0);
    int delta = (p & 1) + 1;
    for (int i = 1; i <= ed; i += delta) if (!mark[i]) {
      int64 d = i * p;
      if (d <= v) {
        lsum[i] -= (lsum[d] - psum) * p;
        lcnt[i] -= lcnt[d] - pcnt;
      } else {
        lsum[i] -= (ssum[n / d] - psum) * p;
        lcnt[i] -= scnt[n / d] - pcnt;
      }
    }
    for (int64 i = q; i <= ed; i += p * delta) mark[i] = true;
    for (int64 i = v; i >= q; --i) {
      ssum[i] -= (ssum[i / p] - psum) * p;
      scnt[i] -= scnt[i / p] - pcnt;
    }
    if (p == k) ret -= lsum[1];
    assert(ret >= 0);
  }
  if (k <= n) ret += k;
  return ret % mod;
}

bool check(int64 n, int64 k) {
  if (n % k) return false;
  for (int64 i = 2; i * i <= n && i < k; ++i) {
    if (n % i == 0) return false;
  }
  return true;
}

int main() {
  int64 l, r, k;
  scanf("%lld%lld%lld", &l, &r, &k);
  printf("%lld\n", (count(r, k) - count(l - 1, k) + mod) % mod);
  return 0;
}

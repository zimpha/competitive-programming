#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
#include <utility>

using int64 = long long;

int64 prime_count(int64 n) {
  const int64 v = static_cast<int64>(sqrt(n));
  std::vector<int64> ssum(v + 1), lsum(v + 1);
  std::vector<bool> mark(v + 1);
  for (int i = 1; i <= v; ++i) {
    ssum[i] = i - 1;
    lsum[i] = n / i - 1;
  }
  for (int64 p = 2; p <= v; ++p) {
    if (ssum[p] == ssum[p - 1]) continue;
    int64 psum = ssum[p - 1], q = p * p, ed = std::min(v, n / q);
    int delta = (p & 1) + 1;
    for (int i = 1; i <= ed; i += delta) if (!mark[i]) {
      int64 d = i * p;
      if (d <= v) {
        lsum[i] -= lsum[d] - psum;
      } else {
        lsum[i] -= ssum[n / d] - psum;
      }
    }
    for (int64 i = q; i <= ed; i += p * delta) mark[i] = true;
    for (int64 i = v; i >= q; --i) {
      ssum[i] -= ssum[i / p] - psum;
    }
  }
  return lsum[1];
}

int main() {
  int64 n;
  scanf("%lld", &n);
  printf("%lld\n", prime_count(n));
}

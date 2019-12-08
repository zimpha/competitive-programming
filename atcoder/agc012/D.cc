#include <cstdio>
#include <vector>
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
  int n, x, y;
  scanf("%d%d%d", &n, &x, &y);
  std::vector<std::vector<int>> c(n);
  for (int i = 0; i < n; ++i) {
    int a, b;
    scanf("%d%d", &a, &b);
    c[a - 1].push_back(b);
  }
  for (int i = 0; i < n; ++i) {
    std::sort(c[i].begin(), c[i].end());
  }
  std::sort(c.begin(), c.end(), [](const std::vector<int> &a, const std::vector<int> &b) {
    if (a.empty()) return false;
    if (b.empty()) return true;
    return a[0] < b[0];
  });
  while (c.back().empty()) c.pop_back();
  n = c.size();
  std::vector<int> ca(n), cb(n);
  int m = 0;
  for (int i = 0; i < n; ++i) {
    int a = 0, b = 0;
    while (a < c[i].size() && c[i][0] + c[i][a] <= x) ++a;
    if (i) {
      while (b < c[i].size() && c[0][0] + c[i][b] <= y) ++b;
    } else if (n > 1) {
      while (b < c[i].size() && c[1][0] + c[i][b] <= y) ++b;
    }
    ca[i] = a, cb[i] = b;
    if (b) m = i;
  }
  n = 0;
  for (int i = 0; i <= m; ++i) n += std::max(ca[i], cb[i]);
  std::vector<int64> fac(n + 1, 1), ifac(n + 1, 1);
  for (int i = 1; i <= n; ++i) {
    fac[i] = fac[i - 1] * i % mod;
    ifac[i] = pow_mod(fac[i], mod - 2);
  }
  int64 ret = fac[n];
  for (int i = 0; i <= m; ++i) {
    ret = ret * ifac[std::max(ca[i], cb[i])] % mod;
  }
  printf("%lld\n", ret);
  return 0;
}

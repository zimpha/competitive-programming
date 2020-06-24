#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using ll = long long;

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> a(n);
  std::vector<ll> b(n);
  int s = 0;
  for (int i = 0; i < n; ++i) {
    scanf("%d%lld", &a[i], &b[i]);
    s += a[i];
  }
  // m = ks + r;
  ll ret = -1;
  std::vector<std::pair<int, int>> frac(n);
  std::vector<int> extra(n);
  for (int r = 0; r < s; ++r) {
    int m = r;
    for (int i = 0; i < n; ++i) {
      extra[i] = r * a[i] / s;
      frac[i] = std::make_pair(-(r * a[i] % s), i);
      m -= extra[i];
    }
    for (int i = 0; i < n; ++i) {
      extra[i] += m / n;
    }
    m %= n;
    std::sort(frac.begin(), frac.end());
    for (int i = 0; i < m; ++i) {
      extra[frac[i].second]++;
    }
    ll k = 0;
    for (int i = 0; i < n; ++i) {
      if (b[i] > extra[i]) {
        // k * a[i] + extra[i] >= b[i], k >= ceil((b[i] - extra[i]) / a[i])
        k = std::max(k, (b[i] - extra[i] + a[i] - 1) / a[i]);
      }
    }
    if (ret == -1 || ret > k * s + r) {
      ret = k * s + r;
    }
  }
  std::cout << ret << std::endl;
  return 0;
}

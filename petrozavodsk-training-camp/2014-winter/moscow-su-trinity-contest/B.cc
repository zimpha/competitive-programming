#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>

using flt = long double;

const int N = 300 + 10;
const flt eps = 1e-12;

std::vector<flt> vs[N];
flt s[N];

int main() {
  int k;
  scanf("%d", &k);
  const flt angle = acos((flt)-1.0) / (k * 2);
  for (int i = 0; i <= k * 2; ++i) s[i] = sin(angle * i);
  for (int x = 1; x < k * 2; ++x) {
    for (int y = 1; y < k * 2 - x; ++y) {
      for (int z = 1; z < k * 2 - y - x; ++z) {
        vs[2 * k - x - z].push_back(s[x] * s[k * 2 - x - y - z] / s[y] / s[z]);
      }
    }
  }
  for (int i = 0; i <= 2 * k; ++i) {
    std::sort(vs[i].begin(), vs[i].end());
  }
  long long ret = 0;
  for (int i = 1; i < k * 2; ++i) {
    const auto& us = vs[k * 2 - i];
    size_t a = 0, b = 0;
    for (auto &x: vs[i]) {
      while (a < us.size() && us[a] < x - eps) ++a;
      while (b < us.size() && us[b] < x + eps) ++b;
      ret += b - a;
    }
  }
  printf("%lld\n", ret);
  return 0;
}

#include <cstdio>
#include <vector>
#include <algorithm>

using int64 = long long;

int main() {
  int d, na, nb, nc;
  while (scanf("%d%d%d%d", &d, &na, &nb, &nc) == 4) {
    std::vector<int> a(na), b(nb), c(nc);
    for (int i = 0; i < na; ++i) scanf("%d", &a[i]);
    for (int i = 0; i < nb; ++i) scanf("%d", &b[i]);
    for (int i = 0; i < nc; ++i) scanf("%d", &c[i]);

    auto inc = [nc](std::vector<int64> &bit, int x, int64 v) {
      for (; x < nc; x += ~x & x + 1) bit[x] += v;
    };

    auto get = [](std::vector<int64> &bit, int x, int64 r = 0) {
      for (; x >= 0; x -= ~x & x + 1) r += bit[x];
      return r;
    };

    std::vector<std::vector<int>> add(nb), sub(nb);
    for (int i = 0; i < na; ++i) {
      int lb = std::lower_bound(b.begin(), b.end(), a[i] - d) - b.begin();
      int rb = std::upper_bound(b.begin(), b.end(), a[i] + d) - b.begin();
      if (lb < rb) {
        add[lb].push_back(i);
        if (rb < nb) sub[rb].push_back(i);
      }
    }

    std::vector<int64> s(nc), si(nc);
    int64 ret = 0;
    for (int i = 0; i < nb; ++i) {
      for (auto &j: add[i]) {
        int lc = std::lower_bound(c.begin(), c.end(), a[j] - d) - c.begin();
        int rc = std::upper_bound(c.begin(), c.end(), a[j] + d) - c.begin();
        inc(s, lc, +1); inc(si, lc, +lc);
        inc(s, rc, -1); inc(si, rc, -rc);
      }
      for (auto &j: sub[i]) {
        int lc = std::lower_bound(c.begin(), c.end(), a[j] - d) - c.begin();
        int rc = std::upper_bound(c.begin(), c.end(), a[j] + d) - c.begin();
        inc(s, lc, -1); inc(si, lc, -lc);
        inc(s, rc, +1); inc(si, rc, +rc);
      }
      int l = std::lower_bound(c.begin(), c.end(), b[i] - d) - c.begin() - 1;
      int r = std::upper_bound(c.begin(), c.end(), b[i] + d) - c.begin() - 1;
      if (l >= 0) ret -= (l + 1) * get(s, l) - get(si, l);
      if (r >= 0) ret += (r + 1) * get(s, r) - get(si, r);
    }
    printf("%lld\n", ret);
  }
  return 0;
}

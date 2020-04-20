#include <cstdio>
#include <vector>
#include <algorithm>

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int na, nb, nc;
    scanf("%d%d%d", &na, &nb, &nc);
    std::vector<int> a(na), b(nb), c(nc);
    for (int i = 0; i < na; ++i) scanf("%d", &a[i]);
    for (int i = 0; i < nb; ++i) scanf("%d", &b[i]);
    for (int i = 0; i < nc; ++i) scanf("%d", &c[i]);
    int ma = *std::min_element(a.begin(), a.end());
    int mb = *std::min_element(b.begin(), b.end());
    int mc = *std::min_element(c.begin(), c.end());
    int ca = 0, cb = 0, cc = 0;
    for (auto &x: a) ca += ma == x;
    for (auto &x: b) cb += mb == x;
    for (auto &x: c) cc += mc == x;
    printf("%d %lld\n", ma + mb + mc, 1ll * ca * cb * cc);
  }
  return 0;
}

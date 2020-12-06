#include <cstdio>
#include <vector>

using i64 = long long;

const int mod = 1e9 + 7;

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    std::vector<int> r(n), c(n);
    for (int i = 0; i < n; ++i) scanf("%d", &r[i]);
    for (int i = 0; i < n; ++i) scanf("%d", &c[i]);
    bool valid = true;
    int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
    i64 ways = 1;
    for (; valid && (x1 != n - 1 || y1 != n - 1 || x2 != n - 1 || y2 != n - 1); ) {
      if (x1 == x2 && y1 == y2) {
        if (r[x1] > 1 && c[y2] > 1) {
          ++y1, ++x2;
          --r[x1], --c[y2];
          ways = ways * 2 % mod;
        } else if (r[x1] == 1) {
          ++x1, ++x2, --c[y2];
        } else if (c[y2] == 1) {
          ++y1, ++y2, --r[x1];
        } else {
          valid = false;
        }
      } else {
        if (!c[y1] || !r[x2]) valid = false;
        if (!r[x1] || !c[y2]) valid = false;
        --c[y1], --r[x2];
        if (r[x1] == 1) ++x1;
        else --r[x1], ++y1;
        if (c[y2] == 1) ++y2;
        else --c[y2], ++x2;
      }
      if (x1 == n || x2 == n || y1 == n || y2 == n) valid = false;
    }
    for (int i = 0; i < n; ++i) {
      if (r[i] != 1) valid = false;
      if (c[i] != 1) valid = false;
    }
    if (x1 != n - 1 || y1 != n - 1) valid = false;
    if (x2 != n - 1 || y2 != n - 1) valid = false;
    if (!valid) ways = 0;
    printf("%lld\n", ways);
  }
  return 0;
}

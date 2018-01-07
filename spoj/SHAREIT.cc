#include <cmath>
#include <cstdio>
#include <vector>

using int64 = long long;

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, m;
    scanf("%d%d", &n, &m);
    std::vector<int64> balance(n);
    std::vector<int> b(n);
    for (int i = 0; i < m; ++i) {
      int f;
      double a;
      scanf("%d%lf", &f, &a);
      int cnt = 0;
      for (int j = 0; j < n; ++j) {
        scanf("%d", &b[j]);
        cnt += b[j];
      }
      int64 tot = floor(a * 100 + 0.5);
      for (int j = 0; j < n; ++j) {
        if (b[j]) {
          balance[j] -= tot / cnt;
          balance[f - 1] += tot / cnt;
        }
      }
    }
    int64 ret = 0;
    for (auto &&x: balance) {
      if (x > 0) ret += x;
    }
    printf("%lld.%02lld\n", ret / 100, ret % 100);
  }
  return 0;
}

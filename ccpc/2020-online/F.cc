#include <cstdio>
#include <vector>

using i64 = long long;

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    std::vector<std::vector<i64>> a(n), b(n), c(n);
    std::vector<std::vector<int>> d(n);
    for (int i = 0, k; i < n - 1; ++i) {
      scanf("%d", &k);
      a[i].resize(k);
      b[i].resize(k + 1);
      c[i].resize(k + 1);
      d[i].resize(k + 1);
      for (int j = 0; j <= k; ++j) {
        scanf("%lld%lld%d", &c[i][j], &b[i][j], &d[i][j]);
        if (j != k) {
          scanf("%lld", &a[i][j]);
          a[i][j] *= 10;
        }
        b[i][j] *= 10;
        --d[i][j];
      }
    }

    auto eval = [&](int t, i64 x, i64 eps) {
      i64 sign = 1;
      while (t != n - 1) {
        int i = std::lower_bound(a[t].begin(), a[t].end(), x + sign * eps) - a[t].begin();
        x = c[t][i] * x + b[t][i];
        sign = sign * c[t][i];
        t = d[t][i];
      }
      return x;
    };

    bool valid = true;
    for (int i = 0; i < n - 1 && valid; ++i) {
      for (size_t j = 0; j < a[i].size() && valid; ++j) {
        i64 left = eval(i, a[i][j], 0);
        i64 right = eval(i, a[i][j], 1);
        valid &= left == right;
      }
    }
    printf("Case #%d: %s\n", cas, valid ? "YES": "NO");
  }
  return 0;
}

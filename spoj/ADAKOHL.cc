#include <cstdio>
#include <vector>
#include <algorithm>
#include <array>

int gcd(int x, int y) {
  return y ? gcd(y, x % y) : x;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    std::vector<int> x(n), y(n), q(n);
    for (int i = 0; i < n; ++i) {
      scanf("%d%d%d", &x[i], &y[i], &q[i]);
    }
    std::vector<std::array<int, 3>> v(n - 1);
    int ret = std::max(0, *std::max_element(q.begin(), q.end()));
    for (int i = 0; i < n; ++i) {
      int m = 0;
      for (int j = 0; j < n; ++j) if (i != j) {
        int dx = x[j] - x[i], dy = y[j] - y[i];
        if (dx < 0 || (dx == 0 && dy < 0)) dx = -dx, dy = -dy;
        int g = gcd(std::abs(dx), std::abs(dy));
        v[m++] = {{dx / g, dy / g, q[j]}};
      }
      std::sort(v.begin(), v.end());
      for (int j = 0, k; j < m; j = k) {
        int sum = 0;
        for (k = j; k < m && v[j][0] == v[k][0] && v[j][1] == v[k][1]; ++k) {
          sum += v[k][2];
        }
        ret = std::max(ret, sum + q[i]);
      }
    }
    printf("%d\n", ret);
  }
  return 0;
}

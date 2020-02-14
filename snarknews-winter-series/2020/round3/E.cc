#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>

const int N = 41, M = N * 100;

int dp[N][M * 2];

void upd(int &x, int y) {
  if (x < y) x = y;
}

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
  std::sort(a.begin(), a.end());
  std::reverse(a.begin(), a.end());
  int ret = -1;
  for (int second = 1; second < n; ++second) {
    std::vector<int> b;
    for (int i = 1; i < n; ++i) if (i != second) b.push_back(a[i]);
    int m = b.size();
    memset(dp, -1, sizeof(dp));
    dp[0][M + a[0] - a[second]] = a[0];
    int s = a[0] + a[second];
    for (int i = 0; i < m; ++i) {
      int* u = dp[i] + M, *v = dp[i + 1] + M;
      for (int d = -s; d <= s; ++d) if (u[d] != -1) {
        upd(v[d + b[i]], u[d] + b[i]);
        if (b[i] <= a[second]) upd(v[d - b[i]], u[d]);
      }
      s += b[i];
    }
    int* u = dp[m] + M;
    for (int d = -s; d <= s; ++d) if (u[d] != -1) {
      int x = u[d], y = x - d;
      if (x > 2 * a[0] && y > 2 * a[second]) {
        if (ret == -1 || ret > std::abs(d)) ret = std::abs(d);
      }
    }
  }
  printf("%d\n", ret);
  return 0;
}

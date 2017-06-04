#include <cstdio>
#include <algorithm>

int main() {
  int n, t, t0;
  scanf("%d%d%d", &n, &t, &t0);
  for (int i = 0; i < n; ++i) {
    int m;
    scanf("%d", &m);
    int mx = 0, ret = 0, sum = 0;
    for (int j = 1; j <= m; ++j) {
      int x;
      scanf("%d", &x);
      sum += x;
      mx = std::max(mx, x);
      if (sum <= t) ret = j;
      if (sum - mx + t0 <= t) ret = j;
    }
    printf("%d\n", ret);
  }
  return 0;
}

#include <cstdio>
#include <vector>

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    std::vector<int> x(k + 1), y(k + 1);
    for (int i = 0; i < k + 1; ++i) {
      scanf("%d%d", &x[i], &y[i]);
    }
    if (k == 1) printf("Case #%d: N\n", cas);
    else {
      int v = (x[0] & 1) ^ (y[0] & 1);
      bool flag = true;
      for (int i = 1; i <= k; ++i) {
        int u = (x[i] & 1) ^ (y[i] & 1);
        if (v != u) flag = false;
      }
      printf("Case #%d: %c\n", cas, "NY"[flag]);
    }
  }
  return 0;
}

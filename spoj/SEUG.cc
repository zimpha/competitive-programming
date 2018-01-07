#include <cstdio>
#include <vector>
#include <algorithm>

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int a, b, h, w;
    scanf("%d%d%d%d", &a, &b, &h, &w);
    int rest = a * b * h - w;
    int need = h - w;
    int n;
    scanf("%d", &n);
    std::vector<int> x(n);
    for (int i = 0; i < n; ++i) {
      scanf("%d", &x[i]);
    }
    std::sort(x.begin(), x.end());
    std::reverse(x.begin(), x.end());
    int ret = 0;
    for (int i = 0; i < n; ++i) {
      need -= x[i];
      ++ret;
      if (need < 0) break;
    }
    printf("%d\n", ret);
  }
  return 0;
}

#include <cstdio>
#include <vector>
#include <algorithm>

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    std::vector<int> even, odd;
    for (int i = 0; i < n; ++i) {
      int x;
      scanf("%d", &x);
      if (i & 1) odd.emplace_back(x);
      else even.emplace_back(x);
    }
    std::sort(odd.begin(), odd.end());
    std::sort(even.begin(), even.end());
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
      if (i & 1) a[i] = odd[i / 2];
      else a[i] = even[i / 2];
    }
    int ret = -1;
    for (int i = 0; i + 1 < n; ++i) {
      if (a[i] > a[i + 1]) {
        ret = i;
        break;
      }
    }
    if (ret == -1) printf("Case #%d: OK\n", cas);
    else printf("Case #%d: %d\n", cas, ret);
  }
  return 0;
}

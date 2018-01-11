#include <cstdio>
#include <vector>

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
      scanf("%d", &a[i]);
    }
    int ret = 0;
    for (int i = n - 1; i >= 0; i -= 2) {
      ret ^= a[i] - a[i - 1];
    }
    if (ret) puts("TAK");
    else puts("NIE");
  }
  return 0;
}

#include <cstdio>
#include <vector>

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    std::vector<int> p(n + 1);
    for (int i = n; i >= 0; --i) {
      scanf("%d", &p[i]);
    }
    if (n % 2 == 1) printf("Case #%d: 1\n0.0\n", cas);
    else printf("Case #%d: 0\n", cas);
  }
  return 0;
}

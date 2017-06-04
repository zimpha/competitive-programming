#include <cstdio>
#include <set>

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, q;
    scanf("%d%d", &n, &q);
    std::set<int> all;
    for (int i = 1; i <= n; ++i) all.insert(i);
    for (int i = 0; i < q; ++i) {
      char op[10];
      int x;
      scanf("%s%d", op, &x);
      if (op[0] == '-') {
        all.erase(x);
        all.erase(n + 1 - x);
      } else {
        for (auto &&e: all) {
          --x;
          if (!x) {
            printf("%d\n", e);
            break;
          }
        }
      }
    }
  }
  return 0;
}

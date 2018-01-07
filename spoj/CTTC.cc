#include <cstdio>
#include <vector>
#include <algorithm>

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    std::vector<int> deg(n), mark(n);
    std::vector<int> stack;
    for (int i = 0, x; i < n * 2; ++i) {
      scanf("%d", &x);
      --x;
      if (!mark[x]) {
        if (!stack.empty()) {
          deg[stack.back()]++;
        }
        stack.push_back(x);
        mark[x] = 1;
      } else {
        stack.pop_back();
      }
    }
    printf("Case %d:\n", cas);
    for (int i = 0; i < n; ++i) {
      printf("%d -> %d\n", i + 1, deg[i]);
    }
    puts("");
  }
  return 0;
}

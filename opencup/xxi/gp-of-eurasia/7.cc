#include <cstdio>
#include <vector>

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    std::vector<int> mark(n);
    int ret = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        int x;
        scanf("%d", &x);
        if (i < j && x && !mark[j]) {
          ++ret;
          mark[j] = 1;
        } 
      }
    }
    printf("%d\n", ret);
  }
  return 0;
}

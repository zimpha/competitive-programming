#include <cstdio>
#include <vector>

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, m;
    scanf("%d%d", &m, &n);
    for (int i = 0; i < m; ++i) scanf("%*s");
    std::vector<int> s(n);
    for (int i = 0; i < n; ++i) scanf("%d", &s[i]);
    for (int i = 0; i < n; ++i) scanf("%*d");
    printf("%d\n", n);
    for (int i = 0; i < n; ++i) {
      printf("1 %d %d\n", s[i], i + 1);
    }
  }
  return 0;
}

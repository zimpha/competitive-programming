#include <cstdio>
#include <vector>

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, m;
    scanf("%d%d", &n, &m);
    std::vector<std::vector<int>> a(n, std::vector<int>(m));
    int v = n * m;
    for (int s = 2; s <= n + m; ++s) {
      for (int i = 1; i <= n; ++i) {
        int j = s - i;
        if (j < 1 || j > m) continue;
        a[i - 1][j - 1] = v--;
      }
    }
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        printf("%d ", a[i][j]);
      }
      puts("");
    }
  }
  return 0;
}

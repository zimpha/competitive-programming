#include <cstdio>
#include <cstring>
#include <vector>

const int N = 500;

int map[N][N];

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int m;
    scanf("%d", &m);
    std::vector<int> a(m);
    memset(map, 0, sizeof(map));
    for (int i = 0; i < m; ++i) {
      scanf("%d", &a[i]);
    }
    printf("Case #%d: ", cas);
    if (a[0] == 0 || a.back() == 0) {
      puts("IMPOSSIBLE");
      continue;
    }
    bool valid = true;
    int last = 0, rows = 0;
    for (int i = 0; i < m; ++i) if (a[i]) {
      int l = last, r = last + a[i];
      for (int j = l; j < r; ++j) {
        if (j < i) {
          for (int k = j; k < i; ++k) map[k - j][k] = 1;
          rows = std::max(rows, i - j + 1);
        } else {
          for (int k = j; k > i; --k) map[j - k][k] = -1;
          rows = std::max(rows, j - i + 1);
        }
      }
      last += a[i];
    }
    printf("%d\n", rows);
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < m; ++j) {
        if (map[i][j] == 0) putchar('.');
        else if (map[i][j] > 0) putchar('\\');
        else putchar('/');
      }
      puts("");
    }
  }
  return 0;
}

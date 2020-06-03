#include <cstdio>
#include <vector>

const int N = 100 + 10;

int a[N][N];

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int sum = 0, sum_row = 0, sum_col = 0;
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        scanf("%d", &a[i][j]);
        if (i == j) sum += a[i][j];
      }
    }
    for (int i = 0; i < n; ++i) {
      std::vector<int> mark(n);
      for (int j = 0; j < n; ++j) mark[a[i][j] - 1] = 1;
      int cnt = 0;
      for (int j = 0; j < n; ++j) cnt += mark[j];
      sum_row += cnt != n;
    }
    for (int j = 0; j < n; ++j) {
      std::vector<int> mark(n);
      for (int i = 0; i < n; ++i) mark[a[i][j] - 1] = 1;
      int cnt = 0;
      for (int i = 0; i < n; ++i) cnt += mark[i];
      sum_col += cnt != n;
    }
    printf("Case #%d: %d %d %d\n", cas, sum, sum_row, sum_col);
  }
  return 0;
}

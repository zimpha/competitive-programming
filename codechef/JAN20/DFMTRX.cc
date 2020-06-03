#include <cstdio>

const int N = 2e3 + 10;

int a[N][N];

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    if (n == 1) {
      puts("Hooray");
      puts("1");
      continue;
    } else if (n % 2 == 1) {
      puts("Boo");
    } else {
      puts("Hooray");
      for (int i = 0; i < n; ++i) a[i][i] = 1;
      for (int i = 0; i < n - 1; ++i) {
        for (int j = i; j < n - 1; ++j) {
          int u = (i + j) % (n - 1);
          int x = j > i ? j : n - 1;
          int y = i;
          a[x][y] = u + 2;
          a[y][x] = u + n + 1;
        }
      }
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
          printf("%d ", a[i][j]);
        }
        puts("");
      }
    }
  }
  return 0;
}

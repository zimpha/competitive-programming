#include <cstdio>

const int N = 100;

int a[N][N], k[3][3];

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        scanf("%d", &a[i][j]);
      }
    }
    int s = 0;
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        scanf("%d", &k[i][j]);
        s += k[i][j];
      }
    }
    if (s != k[0][0]) {
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
          a[i][j] = 0;
        }
      }
    }
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (j) putchar(' ');
        printf("%d", a[i][j]);
      }
      puts("");
    }
  }
  return 0;
}

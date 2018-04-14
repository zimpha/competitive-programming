#include <cstdio>
#include <cstdlib>
#include <cstring>

int mark[4][1000];

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int A;
    scanf("%d", &A);
    memset(mark, 0, sizeof(mark));
    int x = 2, y = 2;
    for (int it = 0; it < 1000; ++it) {
      int cnt = 0;
      for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
          cnt += mark[x + i][y + j];
        }
      }
      if (cnt == 9) y += 3;
      printf("%d %d\n", x, y);
      fflush(stdout);
      int a, b;
      scanf("%d%d", &a, &b);
      if (a == 0 && b == 0) break;
      mark[a][b] = 1;
    }
  }
  return 0;
}

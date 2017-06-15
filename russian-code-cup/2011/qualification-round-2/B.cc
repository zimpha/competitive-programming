#include <cstdio>

const int N = 100;

int ab[N][N], bc[N][N], ac[N][N];
int n, m, k;

void input(int a[][N]) {
  int p;
  scanf("%d", &p);
  for (int i = 0; i < p; ++i) {
    int x, y;
    scanf("%d%d", &x, &y);
    a[x][y] = 1;
  }
}

int main() {
  scanf("%d%d%d", &n, &m, &k);
  input(ab);
  input(bc);
  input(ac);
  int ret = 0;
  for (int x = 1; x <= n; ++x) {
    for (int y = 1; y <= m; ++y) {
      for (int z = 1; z <= k; ++z) {
        if (!ab[x][y] && !bc[y][z] && !ac[x][z]) ++ret;
      }
    }
  }
  printf("%d\n", ret);
  return 0;
}

#include <cstdio>
#include <algorithm>

const int N = 1000 + 10, M = 5000 + 10;

int fa[N][N], col[N][N];
int x1[M], x2[M], y1[M], y2[M];
char c[M][10];

int get(int dsu[], int x) {
  if (x != dsu[x]) dsu[x] = get(dsu, dsu[x]);
  return dsu[x];
}

void color(int dsu[], int col[], int l, int r, int c) {
  while (get(dsu, l) != get(dsu, r)) {
    l = get(dsu, l);
    col[l] = c;
    dsu[l] = get(dsu, l + 1);
  }
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; ++i) {
    scanf("%d%d%d%d%s", &x1[i], &y1[i], &x2[i], &y2[i], c[i]);
    if (x1[i] > x2[i]) std::swap(x1[i], x2[i]);
    if (y1[i] > y2[i]) std::swap(y1[i], y2[i]);
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j <= n; ++j) {
      fa[i][j] = j;
      col[i][j] = -1;
    }
  }
  for (int i = m - 1; i >= 0; --i) {
    for (int j = x1[i] - 1; j < x2[i]; ++j) {
      color(fa[j], col[j], y1[i] - 1, y2[i], c[i][0] == 'b');
    }
  }
  int ret = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      ret += col[i][j] != 1;
    }
  }
  printf("%d\n", ret);
  return 0;
}

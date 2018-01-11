#include <cstdio>

const int N = 600;

int s[N][N], a[N][N];
int n, m;

void add(int x, int y, int v) {
  for (int i = x; i < n; i += ~i & i + 1) {
    for (int j = y; j < m; j += ~j & j + 1) {
      s[i][j] ^= v;
    }
  }
}

int get(int x, int y, int r = 0) {
  for (int i = x; i >= 0; i -= ~i & i + 1) {
    for (int j = y; j >= 0; j -= ~j & j + 1) {
      r ^= s[i][j];
    }
  }
  return r;
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      scanf("%d", &a[i][j]);
      add(i, j, a[i][j]);
    }
  }
  int q;
  scanf("%d", &q);
  for (int i = 0; i < q; ++i) {
    int op, x1, y1, x2, y2, k;
    scanf("%d", &op);
    if (op == 0) {
      scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
      printf("%d\n", get(x2, y2) ^ get(x2, y1 - 1) ^ get(x1 - 1, y2) ^ get(x1 - 1, y1 - 1));
    } else {
      scanf("%d%d%d", &x1, &y1, &k);
      add(x1, y1, a[x1][y1] ^ k);
      a[x1][y1] = k;
    }
  }
  return 0;
}

#include <cstdio>
#include <cstdlib>
#include <cstring>

using uint16 = int;

const int N = 30000 + 10;

struct val {
  uint16 u[10][10];
};

struct Node {
  val* ways;
} T[N << 2];

int dim[N], n, mod;

uint16 ways[10][10], tmp[10][10];

void update(uint16 c[10][10], uint16 a[10][10], uint16 b[10][10], int nl, int nr, int nm) {
  for (int i = 0; i < nl; ++i) {
    for (int j = 0; j < nr; ++j) {
      c[i][j] = 0;
      for (int k = 0; k < nm; ++k) {
        c[i][j] += (int)a[i][k] * b[k][j] % mod;
        if (c[i][j] >= mod) c[i][j] -= mod;
      }
    }
  }
}

void build(int o, int l, int r) {
  T[o].ways = new val();
  if (l + 1 == r) {
    for (int i = 0; i < dim[l]; ++i) {
      for (int j = 0; j < dim[r]; ++j) {
        int x;
        scanf("%d", &x);
        T[o].ways->u[i][j] = x % mod;
      }
    }
    return;
  }
  int m = (l + r) >> 1;
  build(o << 1, l, m);
  build(o << 1 | 1, m, r);
  update(T[o].ways->u, T[o << 1].ways->u, T[o << 1 | 1].ways->u, dim[l], dim[r], dim[m]);
}

void modify(int o, int l, int r, int k, int i, int j, int p) {
  if (l + 1 == r) {
    T[o].ways->u[i][j] = p % mod;
    return;
  }
  int m = (l + r) >> 1;
  if (k < m) modify(o << 1, l, m, k, i, j, p);
  else modify(o << 1 | 1, m, r, k, i, j, p);
  update(T[o].ways->u, T[o << 1].ways->u, T[o << 1 | 1].ways->u, dim[l], dim[r], dim[m]);
}

void query(int o, int l, int r, int L, int R) {
  if (L <= l && R >= r) {
    if (ways[0][0] == mod) {
      memcpy(ways, T[o].ways->u, sizeof(ways));
    } else {
      update(tmp, ways, T[o].ways->u, dim[L], dim[r], dim[l]);
      memcpy(ways, tmp, sizeof(tmp));
    }
    return;
  }
  int m = (l + r) >> 1;
  if (L < m) query(o << 1, l, m, L, R);
  if (R > m) query(o << 1 | 1, m, r, L, R);
}

int main() {
  scanf("%d%d", &mod, &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &dim[i]);
  }
  build(1, 0, n - 1);
  while (true) {
    char op[10];
    scanf("%s", op);
    if (op[0] == 'e') break;
    if (op[0] == 'q') {
      int k, i, l, j;
      scanf("%d%d%d%d", &k, &i, &l, &j);
      ways[0][0] = mod;;
      query(1, 0, n - 1, k - 1, l - 1);
      printf("%d\n", (int)ways[i - 1][j - 1]);
    } else {
      int k, i, j, r;
      scanf("%d%d%d%d", &k, &i, &j, &r);
      modify(1, 0, n - 1, k - 1, i - 1, j - 1, r);
    }
  }
  return 0;
}

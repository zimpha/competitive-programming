#include <cstdio>
#include <cstring>
#include <algorithm>

using int64 = long long;

const int mod = 1e9 + 7;

void mul(int a[2][2], int b[2][2]) {
  int c[2][2];
  c[0][0] = ((int64)a[0][0] * b[0][0] + (int64)a[0][1] * b[1][0]) % mod;
  c[0][1] = ((int64)a[0][0] * b[0][1] + (int64)a[0][1] * b[1][1]) % mod;
  c[1][0] = ((int64)a[1][0] * b[0][0] + (int64)a[1][1] * b[1][0]) % mod;
  c[1][1] = ((int64)a[1][0] * b[0][1] + (int64)a[1][1] * b[1][1]) % mod;
  memcpy(a, c, sizeof(c));
}

const int N = 1e5 + 10;

struct Node {
  int v[2][2], d[2][2];
  void init() {
    memset(v, 0, sizeof(v));
    memset(d, 0, sizeof(d));
    v[0][0] = v[1][1] = 1;
    d[0][0] = d[1][1] = 1;
  }
  void apply(int u[2][2]) {
    mul(v, u);
    mul(d, u);
  }
} T[N << 2];

void update(int o) {
  T[o].v[0][0] = (T[o << 1].v[0][0] + T[o << 1 | 1].v[0][0]) % mod;
  T[o].v[0][1] = (T[o << 1].v[0][1] + T[o << 1 | 1].v[0][1]) % mod;
  T[o].v[1][0] = (T[o << 1].v[1][0] + T[o << 1 | 1].v[1][0]) % mod;
  T[o].v[1][1] = (T[o << 1].v[1][1] + T[o << 1 | 1].v[1][1]) % mod;
}

void push(int o) {
  if (T[o].d[0][0] != 1 || T[o].d[1][1] != 1 || T[o].d[0][1] || T[o].d[1][0]) {
    T[o << 1].apply(T[o].d);
    T[o << 1 | 1].apply(T[o].d);
    T[o].d[0][0] = T[o].d[1][1] = 1;
    T[o].d[0][1] = T[o].d[1][0] = 0;
  }
}

void build(int o, int l, int r) {
  T[o].init();
  if (l + 1 == r) return;
  int m = (l + r) >> 1;
  if (l < m) build(o << 1, l, m);
  if (r > m) build(o << 1 | 1, m, r);
  update(o);
}

void add(int o, int l, int r, int L, int R) {
  if (L <= l && R >= r) {
    static int v[2][2] = {{1, 1}, {1, 0}};
    T[o].apply(v);
    return;
  }
  push(o);
  int m = (l + r) >> 1;
  if (L < m) add(o << 1, l, m, L, R);
  if (R > m) add(o << 1 | 1, m, r, L, R);
  update(o);
}

int64 ret[2][2];
void get(int o, int l, int r, int L, int R) {
  if (L <= l && R >= r) {
    ret[0][0] += T[o].v[0][0];
    ret[0][1] += T[o].v[0][1];
    ret[1][0] += T[o].v[1][0];
    ret[1][1] += T[o].v[1][1];
    return;
  }
  push(o);
  int m = (l + r) >> 1;
  if (L < m) get(o << 1, l, m, L, R);
  if (R > m) get(o << 1 | 1, m, r, L, R);
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  build(1, 0, n);
  for (int i = 0; i < m; ++i) {
    char op[10];
    int l, r;
    scanf("%s%d%d", op, &l, &r);
    if (op[0] == 'D') add(1, 0, n, l - 1, r);
    else {
      memset(ret, 0, sizeof(ret));
      get(1, 0, n, l - 1, r);
      printf("%d\n", int(ret[0][1] % mod));
    }
  }
  return 0;
}

#include <cstdio>
#include <algorithm>

const int S = 2e5 * 30, inf = 2e9;

int ls[S], rs[S], mx[S], sz;

int build(int l, int r) {
  int o = sz++;
  ls[o] = rs[o] = 0;
  if (l + 1 == r) {
    scanf("%d", &mx[o]);
    return o;
  }
  int m = (l + r) >> 1;
  ls[o] = build(l, m);
  rs[o] = build(m, r);
  mx[o] = std::min(mx[ls[o]], mx[rs[o]]);
  return o;
}

int ins(int o, int l, int r, int x, int v) {
  int p = sz++;
  ls[p] = ls[o];
  rs[p] = rs[o];
  if (l + 1 == r) {
    mx[p] = v;
    return p;
  }
  int m = (l + r) >> 1;
  if (x < m) ls[p] = ins(ls[o], l, m, x, v);
  else rs[p] = ins(rs[o], m, r, x, v);
  mx[p] = std::min(mx[ls[p]], mx[rs[p]]);
  return p;
}

int ask(int o, int l, int r, int L, int R) {
  if (L <= l && R >= r) return mx[o];
  int ret = inf, m = (l + r) >> 1;
  if (L < m) ret = std::min(ret, ask(ls[o], l, m, L, R));
  if (R > m) ret = std::min(ret, ask(rs[o], m, r, L, R));
  return ret;
}

int main() {
  ls[0] = rs[0] = 0;
  mx[0] = inf;
  sz = 1;
  int n;
  scanf("%d", &n);
  int ra = build(0, n);
  int rb = build(0, n);
  int q;
  scanf("%d", &q);
  while (q--) {
    int x, y, z;
    scanf("%d%d%d", &x, &y, &z);
    if (x == 1) ra = ins(ra, 0, n, y - 1, z);
    if (x == 2) rb = ins(rb, 0, n, y - 1, z);
    if (x == 3) printf("%d\n", ask(ra, 0, n, y - 1, z));
    if (x == 4) printf("%d\n", ask(rb, 0, n, y - 1, z));
    if (x == 5) ra = rb;
    if (x == 6) rb = ra;
  }
  return 0;
}

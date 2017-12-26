#include <cstdio>
#include <algorithm>
#include <vector>

const int N = 1e5 + 10;

struct node {
  int mx, idx;
  int tag;
  void add(int v) {
    mx += v;
    tag += v;
  }
} T[N << 2];

int a[N];

void update(int rt) {
  T[rt].mx = std::min(T[rt << 1].mx, T[rt << 1 | 1].mx);
  if (T[rt << 1 | 1].mx == T[rt].mx) T[rt].idx = T[rt << 1 | 1].idx;
  else T[rt].idx = T[rt << 1].idx;
}

void pushdown(int rt) {
  T[rt << 1].add(T[rt].tag);
  T[rt << 1 | 1].add(T[rt].tag);
  T[rt].tag = 0;
}

void build(int rt, int l, int r) {
  T[rt].tag = 0;
  if (l + 1 == r) {
    T[rt].mx = a[l];
    T[rt].idx = l;
    return;
  }
  int m = (l + r) >> 1;
  build(rt << 1, l, m);
  build(rt << 1 | 1, m, r);
  update(rt);
}

void ins(int rt, int l, int r, int L, int R, int v) {
  if (L >= R) return;
  if (L <= l && R >= r) {
    T[rt].add(v);
    return;
  }
  pushdown(rt);
  int m = (l + r) >> 1;
  if (L < m) ins(rt << 1, l, m, L, R, v);
  if (R > m) ins(rt << 1 | 1, m, r, L, R, v);
  update(rt);
}

int main() {
  int Ts;
  scanf("%d", &Ts);
  for (int cas = 1; cas <= Ts; ++cas) {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
      scanf("%d", &a[i]);
    }
    build(1, 0, n);
    std::vector<int> ret(n);
    for (int i = n; i >= 1; --i) {
      int p = T[1].idx;
      ret[p] = i;
      ins(1, 0, n, p, p + 1, n * 10);
      ins(1, 0, n, p + 1, n, -1);
    }
    for (int i = 0; i < n; ++i) {
      if (i) putchar(' ');
      printf("%d", ret[i]);
    }
    puts("");
  }
  return 0;
}

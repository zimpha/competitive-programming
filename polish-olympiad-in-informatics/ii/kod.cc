#include <cstdio>
#include <vector>
#include <algorithm>

const int N = 30000 + 10;

struct Node {
  int mx, p;
  int tag;
  void add(int v) {
    mx += v;
    tag += v;
  }
} T[N << 2];

void update(int o) {
  T[o].mx = std::min(T[o << 1].mx, T[o << 1 | 1].mx);
  if (T[o].mx == T[o << 1 | 1].mx) T[o].p = T[o << 1 | 1].p;
  else T[o].p = T[o << 1].p;
}

void push(int o) {
  if (T[o].tag) {
    T[o << 1].add(T[o].tag);
    T[o << 1 | 1].add(T[o].tag);
    T[o].tag = 0;
  }
}

void build(int o, int l, int r) {
  if (l + 1 == r) {
    scanf("%d", &T[o].mx);
    T[o].p = l;
    return;
  }
  int m = (l + r) >> 1;
  build(o << 1, l, m);
  build(o << 1 | 1, m, r);
  update(o);
}

void add(int o, int l, int r, int L, int R) {
  if (L <= l && R >= r) {
    T[o].add(-1);
    return;
  }
  push(o);
  int m = (l + r) >> 1;
  if (L < m) add(o << 1, l, m, L, R);
  if (R > m) add(o << 1 | 1, m, r, L, R);
  update(o);
}

void set(int o, int l, int r, int p) {
  if (l + 1 == r) {
    T[o].mx = 1e9;
    return;
  }
  push(o);
  int m = (l + r) >> 1;
  if (p < m) set(o << 1, l, m, p);
  else set(o << 1 | 1, m, r, p);
  update(o);
}

int main() {
  int n;
  scanf("%d", &n);
  build(1, 0, n);
  std::vector<int> ret(n);
  for (int i = n; i >= 1; --i) {
    if (T[1].mx != 0) {
      puts("NIE");
      return 0;
    }
    ret[T[1].p] = i;
    add(1, 0, n, T[1].p, n);
    set(1, 0, n, T[1].p);
  }
  for (int i = 0; i < n; ++i) printf("%d\n", ret[i]);
  return 0;
}

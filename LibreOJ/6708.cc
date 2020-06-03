#include <cstdio>
#include <cassert>
#include <vector>

const int N = 1e5 + 10;

struct Node {
  int sum, tag;
  void apply(int v, int l, int r) {
    sum = v * (r - l);
    tag = v;
  }
} T[N << 2];

int w[N], bound;

void build(int o, int l, int r) {
  T[o].tag = -1;
  if (l + 1 == r) {
    T[o].sum = w[l] > bound;
    return;
  }
  int m = (l + r) >> 1;
  build(o << 1, l, m);
  build(o << 1 | 1, m, r);
  T[o].sum = T[o << 1].sum + T[o << 1 | 1].sum;
}

void push(int o, int l, int r) {
  if (T[o].tag != -1) {
    T[o << 1].apply(T[o].tag, l, (l + r) >> 1);
    T[o << 1 | 1].apply(T[o].tag, (l + r) >> 1, r);
    T[o].tag = -1;
  }
}

void ins(int o, int l, int r, int L, int R, int v) {
  if (L <= l && R >= r) {
    T[o].apply(v, l, r);
    return;
  }
  push(o, l, r);
  int m = (l + r) >> 1;
  if (L < m) ins(o << 1, l, m, L, R, v);
  if (R > m) ins(o << 1 | 1, m, r, L, R, v);
  T[o].sum = T[o << 1].sum + T[o << 1 | 1].sum;
}

int get(int o, int l, int r, int L, int R) {
  if (L <= l && R >= r) return T[o].sum;
  push(o, l, r);
  int m = (l + r) >> 1, ret = 0;
  if (L < m) ret += get(o << 1, l, m, L, R);
  if (R > m) ret += get(o << 1 | 1, m, r, L, R);
  return ret;
}

int main() {
  int n, m, k;
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 0; i < n; ++i) scanf("%d", &w[i]);
  std::vector<int> op(m), l(m), r(m);
  for (int i = 0; i < m; ++i) {
    scanf("%d%d%d", &op[i], &l[i], &r[i]);
    --l[i];
  }
  int left = 1, right = n;
  while (left < right) {
    bound = (left + right - 1) >> 1;
    build(1, 0, n);
    for (int i = 0; i < m; ++i) {
      int one = get(1, 0, n, l[i], r[i]);
      int zero = r[i] - l[i] - one;
      if (op[i] == 0) {
        if (zero) ins(1, 0, n, l[i], l[i] + zero, 0);
        if (one) ins(1, 0, n, r[i] - one, r[i], 1);
      } else {
        if (one) ins(1, 0, n, l[i], l[i] + one, 1);
        if (zero) ins(1, 0, n, r[i] - zero, r[i], 0);
      }
    }
    if (get(1, 0, n, k - 1, k) == 0) right = bound;
    else left = bound + 1;
  }
  printf("%d\n", left);
  return 0;
}

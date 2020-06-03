#include <cstdio>

using int64 = long long;

const int N = 2e5 + 10;

// eventually it will become 0..0 1..1 s
struct Node {
  int zero, one;
  int64 sum;
} T[N << 2];

Node merge(const Node &a, const Node &b) {
  int zero_a = a.zero, one_a = a.one;
  int zero_b = b.zero, one_b = b.one;
  if (a.sum & 1) ++one_a; else ++zero_b;
  if (zero_b % 2 == 0) return (Node){zero_a + zero_b, one_a + one_b, b.sum + a.sum / 2 * 2};
  else {
    int one = (one_a <= one_b) ? one_b - one_a : one_a - one_b - 1;
    return (Node){a.zero + a.one + b.zero + b.one + 1 - one, one, a.sum + b.sum + a.one + b.one - one};
  }
}

void build(int o, int l, int r) {
  if (l + 1 == r) {
    T[o].zero = T[o].one = 0;
    scanf("%lld", &T[o].sum);
    return;
  }
  int m = (l + r) >> 1;
  build(o << 1, l, m);
  build(o << 1 | 1, m, r);
  T[o] = merge(T[o << 1], T[o << 1 | 1]);
}

void modify(int o, int l, int r, int x, int v) {
  if (l + 1 == r) {
    T[o] = (Node){0, 0, v};
    return;
  }
  int m = (l + r) >> 1;
  if (x < m) modify(o << 1, l, m, x, v);
  else modify(o << 1 | 1, m, r, x, v);
  T[o] = merge(T[o << 1], T[o << 1 | 1]);
}

Node res;
void query(int o, int l, int r, int L, int R) {
  if (L <= l && R >= r) {
    if (res.sum == -1) res = T[o];
    else res = merge(res, T[o]);
    return;
  }
  int m = (l + r) >> 1;
  if (L < m) query(o << 1, l, m, L, R);
  if (R > m) query(o << 1 | 1, m, r, L, R);
}

int main() {
  int n, m;
  scanf("%d", &n);
  build(1, 0, n);
  scanf("%d", &m);
  for (int i = 0; i < m; ++i) {
    int op, x, y;
    scanf("%d%d%d", &op, &x, &y);
    if (op == 1) modify(1, 0, n, x - 1, y);
    else {
      res.sum = -1;
      query(1, 0, n, x - 1, y);
      printf("%d\n", res.zero + !res.sum);
    }
  }
  return 0;
}

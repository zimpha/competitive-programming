#include <cstdio>
#include <algorithm>

using int64 = long long;

const int N = 100000 + 10, M = 11;

int n, mod;
int m, p[M];
int pw[M][N * 15];

template<typename T>
T gcd(T a, T b) {
  return !b ? a : gcd(b, a % b);
}

int64 mod_inv(int64 a, int64 mod) {
  if (gcd(a, mod) != 1) return -1;
  int64 b = mod, s = 1, t = 0;
  while (b) {
    int64 q = a / b;
    std::swap(a -= q * b, b);
    std::swap(s -= q * t, t);
  }
  return s < 0 ? s + mod : s;
}

struct Node {
  int64 sum;
  int64 add[M], mul;
  void push(int64 *ta, int64 tm) {
    sum = sum * tm % mod;
    mul = mul * tm % mod;
    for (int i = 0; i < m; ++i) {
      add[i] += ta[i];
      sum = sum * pw[i][ta[i]] % mod;
    }
  }
  void clear() {
    mul = 1;
    for (int i = 0; i < m; ++i) add[i] = 0;
  }
  void divide(int64 *ta, int64 tm) {
    for (int i = 0; i < m; ++i) add[i] -= ta[i];
    mul = mul * mod_inv(tm, mod) % mod;
    sum = mul;
    for (int i = 0; i < m; ++i) {
      sum = sum * pw[i][add[i]] % mod;
    }
  }
} T[N << 2];

void update(int o) {
  T[o].sum = (T[o << 1].sum + T[o << 1 | 1].sum) % mod;
}

void pushdown(int o) {
  T[o << 1].push(T[o].add, T[o].mul);
  T[o << 1 | 1].push(T[o].add, T[o].mul);
  T[o].clear();
}

void build(int o, int l, int r) {
  T[o].sum = 0; T[o].mul = 1;
  for (int i = 0; i < m; ++i) {
    T[o].add[i] = 0;
  }
  if (l + 1 == r) {
    int x;
    scanf("%d", &x);
    T[o].sum = x % mod;
    for (int i = 0; i < m; ++i) {
      while (x % p[i] == 0) T[o].add[i]++, x /= p[i];
    }
    T[o].mul = x;
    return;
  }
  int mid = (l + r) >> 1;
  build(o << 1, l, mid);
  build(o << 1 | 1, mid, r);
  update(o);
}

void mul(int o, int l, int r, int L, int R, int64 *ta, int64 tm) {
  if (L <= l && R >= r) {
    T[o].push(ta, tm);
    return;
  }
  pushdown(o);
  int mid = (l + r) >> 1;
  if (L < mid) mul(o << 1, l, mid, L, R, ta, tm);
  if (R > mid) mul(o << 1 | 1, mid, r, L, R, ta, tm);
  update(o);
}

void divide(int o, int l, int r, int p, int64 *ta, int64 tm) {
  if (l + 1 == r) {
    T[o].divide(ta, tm);
    return;
  }
  pushdown(o);
  int mid = (l + r) >> 1;
  if (p < mid) divide(o << 1, l, mid, p, ta, tm);
  else divide(o << 1 | 1, mid, r, p, ta, tm);
  update(o);
}

int64 sum(int o, int l, int r, int L, int R) {
  if (L <= l && R >= r) return T[o].sum;
  pushdown(o);
  int64 ret = 0;
  int mid = (l + r) >> 1;
  if (L < mid) ret += sum(o << 1, l, mid, L, R);
  if (R > mid) ret += sum(o << 1 | 1, mid, r, L, R);
  return ret % mod;
}

int main() {
  scanf("%d%d", &n, &mod);
  int mm = mod;
  for (int i = 2; i * i <= mm; ++i) if (mm % i == 0) {
    while (mm % i == 0) mm /= i;
    p[m++] = i;
  }
  if (mm > 1) p[m++] = mm;
  for (int i = 0; i < m; ++i) {
    pw[i][0] = 1;
    for (int j = 1; j < N * 15; ++j) {
      pw[i][j] = (int64)pw[i][j - 1] * p[i] % mod;
    }
  }
  build(1, 0, n);
  int q;
  scanf("%d", &q);
  for (int i = 0; i < q; ++i) {
    int op, l, r, x, y;
    scanf("%d", &op);
    if (op == 1) {
      scanf("%d%d%d", &l, &r, &x);
      int64 add[M];
      for (int i = 0; i < m; ++i) {
        add[i] = 0;
        while (x % p[i] == 0) add[i]++, x /= p[i];
      }
      mul(1, 0, n, l - 1, r, add, x);
    } else if (op == 2) {
      scanf("%d%d", &y, &x);
      int64 add[M];
      for (int i = 0; i < m; ++i) {
        add[i] = 0;
        while (x % p[i] == 0) add[i]++, x /= p[i];
      }
      divide(1, 0, n, y - 1, add, x);
    } else {
      scanf("%d%d", &l, &r);
      printf("%lld\n", sum(1, 0, n, l - 1, r));
    }
  }
  return 0;
}

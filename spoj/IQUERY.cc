#include <cstdio>
#include <vector>

using int64 = long long;
constexpr int mod = 1e9 + 7;
constexpr int N = 1e5 + 10;

struct node {
  int64 prod;
  int cnt[17];
  void set(int v) {
    prod = v + 1;
    for (int i = 0; i < 17; ++i) {
      cnt[i] = v >> i & 1;
    }
  }
} T[N << 2];

void update(int o) {
  T[o].prod = T[o << 1].prod * T[o << 1 | 1].prod % mod;
  for (int i = 0; i < 17; ++i) {
    T[o].cnt[i] = T[o << 1].cnt[i] + T[o << 1 | 1].cnt[i];
  }
}

void build(int rt, int l, int r) {
  if (l + 1 == r) {
    int x;
    scanf("%d", &x);
    T[rt].set(x);
    return;
  }
  int m = (l + r) >> 1;
  build(rt << 1, l, m);
  build(rt << 1 | 1, m, r);
  update(rt);
}

void modify(int o, int l, int r, int x, int v) {
  if (l + 1 == r) {
    T[o].set(v);
    return;
  }
  int m = (l + r) >> 1;
  if (x < m) modify(o << 1, l, m, x, v);
  else modify(o << 1 | 1, m, r, x, v);
  update(o);
}

int64 prod(int o, int l, int r, int L, int R) {
  if (L <= l && R >= r) return T[o].prod;
  int64 ret = 1;
  int m = (l + r) >> 1;
  if (L < m) ret = prod(o << 1, l, m, L, R);
  if (R > m) ret *= prod(o << 1 | 1, m, r, L, R);
  return ret % mod;
}

std::vector<int> bitwise(int o, int l, int r, int L, int R) {
  if (L <= l && R >= r) return {T[o].cnt, T[o].cnt + 17};
  int m = (l + r) >> 1;
  std::vector<int> cnt(17);
  if (L < m) {
    auto t = bitwise(o << 1, l, m, L, R);
    for (int i = 0; i < 17; ++i) cnt[i] += t[i];
  }
  if (R > m) {
    auto t = bitwise(o << 1 | 1, m, r, L, R);
    for (int i = 0; i < 17; ++i) cnt[i] += t[i];
  }
  return cnt;
}

int main() {
  int n, q;
  scanf("%d", &n);
  std::vector<int64> p(n + 1, 1);
  for (int i = 1; i <= n; ++i) {
    p[i] = p[i - 1] * 2 % mod;
  }
  build(1, 0, n);
  scanf("%d", &q);
  while (q--) {
    char op;
    int x, y;
    scanf(" %c%d%d", &op, &x, &y);
    if (op == 'M') printf("%lld\n", (prod(1, 0, n, x - 1, y) + mod - 1) % mod);
    else if (op == 'A') {
      auto cnt = bitwise(1, 0, n, x - 1, y);
      int64 ret = 0;
      for (int i = 0; i < 17; ++i) {
        ret += (p[cnt[i]] - 1) * p[i] % mod;
      }
      printf("%lld\n", ret % mod);
    } else {
      modify(1, 0, n, x - 1, y);
    }
  }
  return 0;
}

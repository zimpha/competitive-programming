#include <cstdio>
#include <vector>

using int64 = long long;

namespace ST {
  const int S = 200000 * 32;
  int cnt[S], ls[S], rs[S], sz;
  void init() {
    cnt[0] = ls[0] = rs[0] = 0;
  }
  int ins(int o, int l, int r, int x) {
    int p = ++sz;
    cnt[p] = cnt[o] + 1;
    ls[p] = ls[o];
    rs[p] = rs[o];
    if (l == r) return p;
    int m = (l + r) >> 1;
    if (x <= m) ls[p] = ins(ls[o], l, m, x);
    else rs[p] = ins(rs[o], m + 1, r, x);
    return p;
  }
  int get(int a, int b, int l, int r, int L, int R) {
    if (L > R) return 0;
    if (L <= l && R >= r) return cnt[a] - cnt[b];
    int m = (l + r) >> 1, ret = 0;
    if (L <= m) ret += get(ls[a], ls[b], l, m, L, R);
    if (R > m) ret += get(rs[a], rs[b], m + 1, r, L, R);
    return ret;
  }
}

int main() {
  int n, q;
  scanf("%d%d", &n, &q);
  std::vector<int> rt(n + 1, 0);
  ST::init();
  for (int i = 1; i <= n; ++i) {
    int x;
    scanf("%d", &x);
    rt[i] = ST::ins(rt[i - 1], 1, n, x);
  }
  auto comb = [](int64 x) {
    //printf("%lld ", x);
    return x * (x - 1) / 2;
  };
  for (int i = 0; i < q; ++i) {
    int l, d, r, u;
    scanf("%d%d%d%d", &l, &d, &r, &u);
    int64 ret = comb(n);

    ret -= comb(ST::get(rt[n], rt[r], 1, n, 1, n));
    ret -= comb(ST::get(rt[n], rt[0], 1, n, 1, d - 1));
    ret -= comb(ST::get(rt[n], rt[0], 1, n, u + 1, n));
    ret -= comb(ST::get(rt[l - 1], rt[0], 1, n, 1, n));

    ret += comb(ST::get(rt[l - 1], rt[0], 1, n, u + 1, n));
    ret += comb(ST::get(rt[l - 1], rt[0], 1, n, 1, d - 1));
    ret += comb(ST::get(rt[n], rt[r], 1, n, 1, d - 1));
    ret += comb(ST::get(rt[n], rt[r], 1, n, u + 1, n));
    printf("%lld\n", ret);
  }
  return 0;
}
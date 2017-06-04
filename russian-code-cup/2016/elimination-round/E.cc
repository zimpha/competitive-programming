#include <cstdio>
#include <vector>
#include <algorithm>

using ll = long long;

const int N = 150000 + 10, S = N * 20;

std::vector<int> xs;
int cnt[S], ls[S], rs[S], rt[N];
ll sum[S];
int a[N], n, sz, q, m;

int ins(int o, int l, int r, int x) {
  int p = sz++;
  cnt[p] = cnt[o] + 1;
  sum[p] = sum[o] + xs[x];
  ls[p] = ls[o];
  rs[p] = rs[o];
  if (l + 1 == r) return p;
  int m = (l + r) >> 1;
  if (x < m) ls[p] = ins(ls[o], l, m, x);
  else rs[p] = ins(rs[o], m, r, x);
  return p;
}

ll get_sum(int a, int b, int l, int r, int k) {
  if (l + 1 == r) return 1ll * k * xs[l];
  int lc = cnt[ls[a]] - cnt[ls[b]];
  int m = (l + r) >> 1;
  if (lc >= k) return get_sum(ls[a], ls[b], l, m, k);
  else return sum[ls[a]] - sum[ls[b]] + get_sum(rs[a], rs[b], m, r, k - lc);
}

int get_cnt(int a, int b, int l, int r, ll bound) {
  if (l + 1 == r) return cnt[a] - cnt[b];
  int m = (l + r) >> 1;
  if (bound < xs[m]) return get_cnt(ls[a], ls[b], l, m, bound);
  else return cnt[ls[a]] - cnt[ls[b]] + get_cnt(rs[a], rs[b], m, r, bound);
}

ll solve(int l, int r) {
  int n = r - l;
  if (get_sum(rt[r], rt[l], 0, m, 1) != 1) return 1;
  for (int i = 1; i < n; ) {
    ll s = get_sum(rt[r], rt[l], 0, m, i);
    int p = get_cnt(rt[r], rt[l], 0, m, s + 1);
    if (p == i) return s + 1;
    else i = p;
  }
  return get_sum(rt[r], rt[l], 0, m, n) + 1;
}

int main() {
  scanf("%d%d", &n, &q);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
    xs.push_back(a[i]);
  }
  std::sort(xs.begin(), xs.end());
  xs.erase(std::unique(xs.begin(), xs.end()), xs.end());
  rt[0] = ls[0] = rs[0] = cnt[0] = sum[0] = sz = 0;
  ++sz;
  m = xs.size();
  for (int i = 0; i < n; ++i) {
    int x = std::lower_bound(xs.begin(), xs.end(), a[i]) - xs.begin();
    rt[i + 1] = ins(rt[i], 0, m, x);
  }
  for (int i = 0; i < q; ++i) {
    int l, r;
    scanf("%d%d", &l, &r);
    printf("%lld\n", solve(l - 1, r));
  }
  return 0;
}

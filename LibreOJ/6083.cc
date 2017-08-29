#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>

using ll = long long;

const int N = 100000 + 10, M = N * 60;

std::vector<std::pair<int, int>> bit[32];
std::vector<int> cnt[32];
int a[N], nx[N], n, q;
int rt[N];

namespace ST {
int ls[M], rs[M];
ll sl[M], slr[M], cnt[M];
int sz;

int ins(int o, int l, int r, int x, int v) {
  int p = sz++;
  ls[p] = ls[o];
  rs[p] = rs[o];
  sl[p] = sl[o] + v;
  cnt[p] = cnt[o] + 1;
  slr[p] = slr[o] + x - v + 1;
  if (l + 1 == r) return p;
  int m = (l + r) >> 1;
  if (x < m) ls[p] = ins(ls[o], l, m, x, v);
  else rs[p] = ins(rs[o], m, r, x, v);
  return p;
}

int get_cnt(int a, int b, int l, int r, int L, int R) {
  if (L <= l && R >= r) return cnt[a] - cnt[b];
  int m = (l + r) >> 1, ret = 0;
  if (L < m) ret += get_cnt(ls[a], ls[b], l, m, L, R);
  if (R > m) ret += get_cnt(rs[a], rs[b], m, r, L, R);
  return ret;
}

ll get_sl(int a, int b, int l, int r, int L, int R) {
  if (L <= l && R >= r) return sl[a] - sl[b];
  int m = (l + r) >> 1;
  ll ret = 0;
  if (L < m) ret += get_sl(ls[a], ls[b], l, m, L, R);
  if (R > m) ret += get_sl(rs[a], rs[b], m, r, L, R);
  return ret;
}

ll get_slr(int a, int b, int l, int r, int L, int R) {
  if (L <= l && R >= r) return slr[a] - slr[b];
  int m = (l + r) >> 1;
  ll ret = 0;
  if (L < m) ret += get_slr(ls[a], ls[b], l, m, L, R);
  if (R > m) ret += get_slr(rs[a], rs[b], m, r, L, R);
  return ret;
}
}

void brute() {
  for (int i = 1; i <= n; ++i) {
    int j = i, p = a[i - 1];
    while (j + 1 <= n && (a[j + 1] ^ p) >= (a[j] ^ p)) ++j;
    assert(j == nx[i]);
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", a + i);
    a[i] ^= a[i - 1];
  }
  for (int i = 1; i <= n; ++i) {
    int p = a[i] ^ a[i - 1];
    for (int b = 30; b >= 0; --b) {
      if (p >> b & 1) {
        bit[b].emplace_back(i, a[i - 1] >> b & 1);
        break;
      }
    }
  }
  for (int b = 30; b >= 0; --b) if (bit[b].size()) {
    cnt[b].assign(bit[b].size(), 0);
    for (int i = cnt[b].size() - 1; i >= 0; --i) {
      if (i == cnt[b].size() - 1) cnt[b][i] = 1;
      else {
        if (bit[b][i].second == bit[b][i + 1].second) cnt[b][i] = cnt[b][i + 1] + 1;
        else cnt[b][i] = 1;
      }
    }
  }
  for (int i = 1; i <= n; ++i) {
    int p = a[i - 1];
    nx[i] = i;
    int r = n + 1;
    for (int b = 0; b <= 30; ++b) {
      int o = p >> b & 1, tmp;
      int j = std::upper_bound(bit[b].begin(), bit[b].end(), std::make_pair(i + 1, -1)) - bit[b].begin();
      if (j == bit[b].size()) continue;
      if (bit[b][j].second == o) {
        j += cnt[b][j];
        if (j == bit[b].size()) tmp = n;
        else tmp = bit[b][j].first - 1;
      } else {
        tmp = bit[b][j].first - 1;
      }
      r = std::min(r, tmp);
    }
    if (r != n + 1) nx[i] = r;
  }
  rt[0] = 0;
  ST::sz = 1;
  for (int i = 1; i <= n; ++i) {
    rt[i] = ST::ins(rt[i - 1], 1, n + 1, nx[i], i);
  }
  int q;
  scanf("%d", &q);
  ll last = 0;
  for (int i = 0; i < q; ++i) {
    ll a, b;
    scanf("%lld%lld", &a, &b);
    a = (a + last) % n + 1;
    b = (b + last) % n + 1;
    if (a > b) std::swap(a, b);
    last = ST::get_slr(rt[b], rt[a - 1], 1, n + 1, a, b + 1);
    if (b + 1 <= n) {
      ll c = ST::get_cnt(rt[b], rt[a - 1], 1, n + 1, b + 1, n + 1);
      last -= ST::get_sl(rt[b], rt[a - 1], 1, n + 1, b + 1, n + 1);
      last += c * (b + 1);
    }
    printf("%lld\n", last);
  }
  return 0;
}

#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>

using int64 = long long;

const int N = 1e5 + 10;

struct node {
  int64 max_now, max_his;
  int64 tag_now, tag_his;
  void mark(int64 x, int64 y) {
    max_his = std::max(max_his, max_now + y);
    tag_his = std::max(tag_his, tag_now + y);
    max_now += x;
    tag_now += x;
  }
} T[N << 2];

void pushdown(int rt) {
  T[rt << 1].mark(T[rt].tag_now, T[rt].tag_his);
  T[rt << 1 | 1].mark(T[rt].tag_now, T[rt].tag_his);
  T[rt].tag_now = T[rt].tag_his = 0;
}

void update(int rt) {
  T[rt].max_now = std::max(T[rt << 1].max_now, T[rt << 1 | 1].max_now);
  T[rt].max_his = std::max(T[rt << 1].max_his, T[rt << 1 | 1].max_his);
}

void modify(int rt, int l, int r, int L, int R, int v) {
  if (L <= l && R >= r) {
    T[rt].mark(v, 0);
    return;
  }
  pushdown(rt);
  int m = (l + r) >> 1;
  if (L < m) modify(rt << 1, l, m, L, R, v);
  if (R > m) modify(rt << 1 | 1, m, r, L, R, v);
  update(rt);
}

int64 query(int rt, int l, int r, int L, int R) {
  if (L <= l && r <= R) return std::max(T[rt].max_now, T[rt].max_his);
  pushdown(rt);
  int m = (l + r) >> 1;
  int64 ret = 0;
  if (L < m) ret = std::max(ret, query(rt << 1, l, m, L, R));
  if (R > m) ret = std::max(ret, query(rt << 1 | 1, m, r, L, R));
  return ret;
}

std::vector<int> ql[N];

int main() {
  int n;
  scanf("%d", &n);
  std::map<int, int> mp;
  std::vector<int> a(n), prev(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
    if (!mp.count(a[i])) mp[a[i]] = -1;
    prev[i] = mp[a[i]];
    mp[a[i]] = i;
  }
  int m;
  scanf("%d", &m);
  std::vector<int> l(m), r(m);
  std::vector<int64> ret(m);
  for (int i = 0; i < m; ++i) {
    scanf("%d%d", &l[i], &r[i]);
    --l[i], --r[i];
    ql[r[i]].emplace_back(i);
  }
  for (int i = 0; i < n; ++i) {
    modify(1, 0, n, prev[i] + 1, i + 1, a[i]);
    for (auto &&q: ql[i]) {
      ret[q] = query(1, 0, n, l[q], i + 1);
    }
  }
  for (int i = 0; i < m; ++i) {
    printf("%lld\n", ret[i]);
  }
  return 0;
}

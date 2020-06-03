#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>

using int64 = long long;

const int N = 5e4 + 10;

struct Node {
  int64 mx, h_mx;
  int64 add, h_add;
  void apply(int64 v, int64 h_v) {
    h_mx = std::max(h_mx, mx + h_v);
    h_add = std::max(h_add, add + h_v);
    mx += v; add += v;
  }
} T[N << 2];

void push(int o) {
  if (T[o].add || T[o].h_add) {
    T[o << 1].apply(T[o].add, T[o].h_add);
    T[o << 1 | 1].apply(T[o].add, T[o].h_add);
    T[o].add = T[o].h_add = 0;
  }
}
void update(int o) {
  T[o].mx = std::max(T[o << 1].mx, T[o << 1 | 1].mx);
  T[o].h_mx = std::max(T[o << 1].h_mx, T[o << 1 | 1].h_mx);
}
void build(int o, int l, int r) {
  T[o].add = T[o].h_add = 0;
  T[o].mx = T[o].h_mx = 0;
  if (l + 1 == r) return;
  int m = (l + r) >> 1;
  build(o << 1, l, m);
  build(o << 1 | 1, m, r);
}
void modify(int o, int l, int r, int L, int R, int64 v) {
  if (L <= l && r <= R) {
    T[o].apply(v, std::max<int64>(0, v));
    return;
  }
  push(o);
  int m = (l + r) >> 1;
  if (L < m) modify(o << 1, l, m, L, R, v);
  if (R > m) modify(o << 1 | 1, m, r, L, R, v);
  update(o);
}
int64 ask(int o, int l, int r, int L, int R) {
  if (L <= l && r <= R) return T[o].h_mx;
  push(o);
  int m = (l + r) >> 1;
  int64 ret = 0;
  if (L < m) ret = std::max(ret, ask(o << 1, l, m, L, R));
  if (R > m) ret = std::max(ret, ask(o << 1 | 1, m, r, L, R));
  return ret;
}

std::vector<int> add[N], sub[N];
std::vector<int> query[N];

int main() {
  int n, m1, m2;
  scanf("%d%d%d", &n, &m1, &m2);
  std::vector<int> x1(m1 + m2), y1(m1 + m2), x2(m1 + m2), y2(m1 + m2), w(m1);
  int64 bound = 0;
  for (int i = 0; i < m1 + m2; ++i) {
    scanf("%d%d%d%d", &x1[i], &y1[i], &x2[i], &y2[i]);
    --x1[i], --y1[i];
    if (i < m1) {
      scanf("%d", &w[i]);
      add[x1[i]].push_back(i);
      sub[x2[i]].push_back(i);
      bound += w[i] * 2;
    }
  }
  std::vector<int64> ret(m2), sum(m2);
  for (int len = 1; len <= n; len *= 2) {
    for (int i = 0; i < n; ++i) query[i].clear();
    for (int i = m1; i < m1 + m2; ++i) {
      int l = (x1[i] + len - 1) / len, r = x2[i] / len;
      if (l >= r) continue;
      if (l & 1) query[l].push_back(i);
      if (r & 1) query[r - 1].push_back(i);
    }
    build(1, 0, n);
    int cnt = 0;
    for (int i = 0; i < n; i += len) {
      for (int j = i; j < n && j < i + len; ++j) {
        for (auto &e: sub[j]) modify(1, 0, n, y1[e], y2[e], -w[e]);
        for (auto &e: add[j]) modify(1, 0, n, y1[e], y2[e], +w[e]);
        if (i == j) {
          modify(1, 0, n, 0, n, bound);
          ++cnt;
        }
      }
      for (auto &e: query[i / len]) {
        ret[e - m1] = std::max(ret[e - m1], ask(1, 0, n, y1[e], y2[e]) - bound * cnt);
      }
    }
  }
  for (int i = 0; i < m2; ++i) {
    printf("%lld\n", ret[i]);
  }
  return 0;
}

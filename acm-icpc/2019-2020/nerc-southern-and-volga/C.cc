#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>

using int64 = long long;

const int N = 2e5 + 10;

struct Node {
  std::pair<int64, int> mx;
  int64 delta;
  void apply(int64 v) {
    delta += v;
    mx.first += v;
  }
} T[N << 2];

std::vector<std::pair<int, int64>> iv[N];

void build(int o, int l, int r, int64 k) {
  T[o].delta = 0;
  if (l + 1 == r) {
    T[o].mx = {k * l, l};
    return;
  }
  int m = (l + r) >> 1;
  build(o << 1, l, m, k);
  build(o << 1 | 1, m, r, k);
  T[o].mx = std::max(T[o << 1].mx, T[o << 1 | 1].mx);
}

void push(int o) {
  if (T[o].delta) {
    T[o << 1].apply(T[o].delta);
    T[o << 1 | 1].apply(T[o].delta);
    T[o].delta = 0;
  }
}

void add(int o, int l, int r, int L, int R, int64 v) {
  if (L <= l && R >= r) {
    T[o].apply(v);
    return;
  }
  push(o);
  int m = (l + r) >> 1;
  if (L < m) add(o << 1, l, m, L, R, v);
  if (R > m) add(o << 1 | 1, m, r, L, R, v);
  T[o].mx = std::max(T[o << 1].mx, T[o << 1 | 1].mx);
}

std::pair<int64, int> get(int o, int l, int r, int L, int R) {
  if (L <= l && R >= r) return T[o].mx;
  push(o);
  std::pair<int64, int> ret = {-1, -1};
  int m = (l + r) >> 1;
  if (L < m) ret = std::max(ret, get(o << 1, l, m, L, R));
  if (R > m) ret = std::max(ret, get(o << 1 | 1, m, r, L, R));
  return ret;
}

int main() {
  int n;
  int64 k;
  scanf("%d%lld", &n, &k);
  std::vector<int> l(n), r(n);
  for (int i = 0; i < n; ++i) {
    int64 p;
    scanf("%d%d%lld", &l[i], &r[i], &p);
    --l[i], --r[i];
    iv[r[i]].emplace_back(l[i], p);
  }
  build(1, 0, 200000, k);
  int64 best = -1;
  int best_l, best_r;
  for (int i = 0; i < 200000; ++i) {
    for (auto &e: iv[i]) add(1, 0, 200000, 0, e.first + 1, e.second);
    auto rt = get(1, 0, 200000, 0, i + 1);
    if (rt.first - k * (i + 1) > 0 && (best == -1 || best < rt.first - k * (i + 1))) {
      best = rt.first - k * (i + 1);
      best_l = rt.second;
      best_r = i;
    }
  }
  if (best == -1) puts("0");
  else {
    std::vector<int> ret;
    for (int i = 0; i < n; ++i) {
      if (l[i] >= best_l && r[i] <= best_r) {
        ret.push_back(i);
      }
    }
    printf("%lld %d %d %d\n", best, best_l + 1, best_r + 1, (int)ret.size());
    for (auto &x: ret) printf("%d ", x + 1);
    puts("");
  }
  return 0;
}

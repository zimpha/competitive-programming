#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <set>
#include <functional>

using int64 = long long;

const int64 is_query = -(1LL<<62), inf = 1ll << 62;
struct Line {// y = m * x + b
  int64 m, b;
  mutable std::function<const Line*()> succ;
  bool operator<(const Line& rhs) const {
    if (rhs.b != is_query) return m < rhs.m;
    const Line* s = succ();
    if (!s) return 0;
    return b - s->b < (s->m - m) * rhs.m;
  }
};
// wiLL maintain lower huLL for maximum
struct HuLLDynamic: public std::multiset<Line> {
  bool bad(iterator y) {
    auto z = next(y);
    if (y == begin()) {
      if (z == end()) return 0;
      return y->m == z->m && y->b <= z->b;
    }
    auto x = prev(y);
    if (z == end()) return y->m == x->m && y->b <= x->b;
    return (x->b - y->b)*(z->m - y->m) >= (y->b - z->b)*(y->m - x->m);
  }
  void ins(int64 m, int64 b) {
    auto y = insert({m, b});
    y->succ = [=] {return next(y) == end()?0:&*next(y);};
    if (bad(y)) {erase(y); return;}
    while (next(y) != end() && bad(next(y))) erase(next(y));
    while (y != begin() && bad(prev(y))) erase(prev(y));
  }
  int64 eval(int64 x) {
    auto l = lower_bound((Line){x,is_query});
    if (l == end()) return -inf;
    return l->m * x + l->b;
  }
};

const int N = 2e5 + 10;

HuLLDynamic hull[N << 2];

void build(int o, int l, int r) {
  hull[o].clear();
  if (l + 1 == r) return;
  int m = (l + r) >> 1;
  build(o << 1, l, m);
  build(o << 1 | 1, m, r);
}

void add(int o, int l, int r, int x, int64 a, int64 b) {
  hull[o].ins(a, b);
  if (l + 1 == r) return;
  int m = (l + r) >> 1;
  if (x < m) add(o << 1, l, m, x, a, b);
  else add(o << 1 | 1, m, r, x, a, b);
}

int get(int o, int l, int r, int64 x, int64 y) {
  if (l + 1 == r) return l;
  int m = (l + r) >> 1;
  if (hull[o << 1 | 1].eval(x) >= y) return get(o << 1 | 1, m, r, x, y);
  else return get(o << 1, l, m, x, y);
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    build(1, 0, n + 1);
    int ret = 0;
    for (int i = 0; i < n; ++i) {
      int64 a, b, x, y;
      scanf("%lld%lld%lld%lld", &a, &b, &x, &y);
      int now = 0;
      if (hull[1].empty() || hull[1].eval(x) < y) now = 1;
      else now = get(1, 0, n + 1, x, y) + 1;
      add(1, 0, n + 1, now, a, b);
      if (now > ret) ret = now;
    }
    printf("%d\n", ret);
  }
  return 0;
}

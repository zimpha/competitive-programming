#include <cstdio>
#include <cstdlib>
#include <set>
#include <vector>
#include <functional>
#include <algorithm>

using int64 = long long;

const int64 is_query = -(1ll << 62), inf = 1ll << 62;

void upd(int64 &x, int64 y) {
  if (x == -1 || x > y) x = y;
}

struct Line {// y = m * x + b
  int64 m, b;
  mutable std::function<const Line*()> succ;
  bool operator<(const Line& rhs) const {
    if (rhs.b != is_query) return m < rhs.m;
    const Line* s = succ();
    if (!s) return 0;
    return b - s->b < (s->m - m) * rhs.m;
  }
};// wiint64 maintain lower huint64 for maximum
struct HullDynamic: public std::multiset<Line> {
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
    //printf("add line %lldx+%lld\n", m, b);
    auto y = insert({m, b});
    y->succ = [=] {return next(y) == end()?0:&*next(y);};
    if (bad(y)) {erase(y); return;}
    while (next(y) != end() && bad(next(y))) erase(next(y));
    while (y != begin() && bad(prev(y))) erase(prev(y));
  }
  int64 eval(int64 x) {
    auto l = lower_bound((Line){x,is_query});
    //printf("eval x=%lld\n", x);
    if (l == end()) return -inf;
    return l->m * x + l->b;
  }
};

int main() {
  int n, m, q;
  scanf("%d%d%d", &n, &m, &q);
  std::vector<int> d(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &d[i]);
  }
  std::vector<char> op(m);
  std::vector<int> b(m), t(m);
  for (int i = 0; i < m; ++i) {
    scanf(" %c%d%d", &op[i], &b[i], &t[i]);
    --b[i];
  }
  std::vector<int> x(q), y(q);
  std::vector<int64> ret(q, -1);
  for (int i = 0; i < q; ++i) {
    scanf("%d%d", &x[i], &y[i]);
    --x[i], --y[i];
  }
  for (int it = 0; it < 2; ++it) {
    std::vector<int64> sum(n);
    for (int i = n - 1; i >= 0; --i) {
      sum[i] = d[i];
      if (i + 1 < n) sum[i] += sum[i + 1];
    }
    std::vector<std::vector<int>> train(n);
    std::vector<std::vector<int>> query(n);
    for (int i = 0; i < m; ++i) if (op[i] == 'R') {
      train[b[i]].push_back(i);
    }
    for (int i = 0; i < q; ++i) {
      query[x[i]].push_back(i);
    }
    HullDynamic hull1, hull2;
    for (int i = 0; i < n; ++i) {
      for (auto &j: train[i]) {
        hull1.ins(t[j], -t[j] * sum[b[j]]);;
        hull2.ins(t[j], -t[j] * (sum[b[j]] + sum[0]));;
      }
      for (auto &j: query[i]) {
        if (x[j] < y[j]) upd(ret[j], -hull1.eval(sum[y[j]]));
        else upd(ret[j], -hull2.eval(sum[y[j]]));
      }
    }
    //for (auto &x: ret) printf("%lld ", x);
    //puts("");
    hull1.clear(); hull2.clear();
    for (int i = n - 1; i >= 0; --i) {
      for (auto &j: query[i]) {
        if (x[j] < y[j]) upd(ret[j], -hull1.eval(sum[y[j]]));
        else upd(ret[j], -hull2.eval(sum[y[j]]));
      }
      for (auto &j: train[i]) {
        hull1.ins(t[j], -t[j] * (sum[b[j]] + sum[0]));;
        hull2.ins(t[j], -t[j] * (sum[b[j]] + sum[0] * 2));;
      }
    }
    //for (auto &x: ret) printf("%lld ", x);
    //puts("");
    for (int i = 0; i < q; ++i) {
      x[i] = n - 1 - x[i];
      y[i] = n - 1 - y[i];
    }
    for (int i = 0; i < m; ++i) {
      b[i] = n - 1 - b[i];
      op[i] ^= 'L' ^ 'R';
    }
    std::reverse(d.begin(), d.begin() + n - 1);
  }
  for (int i = 0; i < q; ++i) {
    printf("%lld\n", ret[i]);
  }
  return 0;
}

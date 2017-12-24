#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using int64 = long long;

constexpr int N = 2e5 + 10, B = 600;

std::vector<int> ql[B];
int a[N], xs[N];
int n, m, q;

namespace mo {
  int stk[N * 3], top;
  int cnt[N], ret;
  void init() {
    top = 0;
    ret = 0;
    memset(cnt, 0, sizeof(*cnt) * m);
  }
  void add(int x) {
    stk[top++] = ret;
    stk[top++] = x;
    cnt[x]++;
    ret = std::max(ret, cnt[x]);
  }
  void restore(int checkpoint) {
    while (top > checkpoint) {
      cnt[stk[--top]]--;
      ret = stk[--top];
    }
  };
};

int main() {
  scanf("%d%d", &n, &q);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
    xs[i] = a[i];
  }
  std::sort(xs, xs + n);
  m = std::unique(xs, xs + n) - xs;
  for (int i = 0; i < n; ++i) {
    a[i] = std::lower_bound(xs, xs + m, a[i]) - xs;
  }
  std::vector<int> l(q), r(q), k(q);
  for (int i = 0; i < q; ++i) {
    scanf("%d%d%d", &l[i], &r[i], &k[i]);
    --l[i], --r[i];
    ql[l[i] / B].emplace_back(i);
  }
  for (int i = 0; i < B; ++i) {
    std::sort(ql[i].begin(), ql[i].end(), [&](int x, int y) {
        return r[x] > r[y];
        });
  }
  std::vector<int> ret(q);
  for (int it = 0; it < B; ++it) {
    int st = it * B, ed = it * B + B;
    if (st >= n) break;
    mo::init();
    auto &qv = ql[it];
    while (!qv.empty() && r[qv.back()] < ed) {
      int x = l[qv.back()], y = r[qv.back()];
      int check = mo::top;
      for (int i = x; i <= y; ++i) mo::add(a[i]);
      ret[qv.back()] = mo::ret;
      mo::restore(check);
      qv.pop_back();
    }
    for (int i = ed; !qv.empty(); ) {
      int x = l[qv.back()], y = r[qv.back()];
      while (i <= y) mo::add(a[i++]);
      int check = mo::top;
      for (int j = ed - 1; j >= x; --j) mo::add(a[j]);
      ret[qv.back()] = mo::ret;
      mo::restore(check);
      qv.pop_back();
    }
  }
  for (int i = 0; i < q; ++i) {
    if ((int64)ret[i] * k[i] >= r[i] - l[i] + 1) puts("YES");
    else puts("NO");
  }
  return 0;
}

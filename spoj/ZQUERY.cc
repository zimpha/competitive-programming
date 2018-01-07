#include <cmath>
#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>

const int N = 5e5 + 10;

namespace mo {
  int mx[N], mi[N], ret;
  std::vector<std::pair<int&, int>> history;
  void init(int m) {
    ret = 0;
    for (int i = 0; i <= m; ++i) {
      mx[i] = -1;
      mi[i] = N;
    }
    history.clear();
  }
  void change(int &a, int b) {
    history.emplace_back(a, a);
    a = b;
  }
  void add(int x, int v) {
    if (v < mi[x]) change(mi[x], v);
    if (v > mx[x]) change(mx[x], v);
    int t = mx[x] - mi[x];
    if (t > ret) change(ret, t);
  }
  void rollback(size_t s) {
    while (history.size() > s) {
      history.back().first = history.back().second;
      history.pop_back();
    }
  }
}

std::vector<int> ql[N];

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  std::vector<int> a(n + 1);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
    a[i] += a[i - 1];
  }
  auto xs = a;
  std::sort(xs.begin(), xs.end());
  xs.erase(std::unique(xs.begin(), xs.end()), xs.end());
  for (int i = 0; i <= n; ++i) {
    a[i] = std::lower_bound(xs.begin(), xs.end(), a[i]) - xs.begin();
  }
  int block = sqrt(n + 1);
  std::vector<int> l(m), r(m), ret(m);
  for (int i = 0; i < m; ++i) {
    scanf("%d%d", &l[i], &r[i]);
    ql[(--l[i]) / block].emplace_back(i);
  }
  for (int b = 0; b <= n; ++b) {
    auto &v = ql[b];
    if (v.empty()) continue;
    std::sort(v.begin(), v.end(), [&](int x, int y) {
      return r[x] > r[y];
    });
    mo::init(xs.size());
    int L = b * block, R = L + block;
    while (!v.empty() && r[v.back()] < R) {
      int id = v.back(), check = mo::history.size();
      for (int i = l[id]; i <= r[id]; ++i) {
        mo::add(a[i], i);
      }
      ret[id] = mo::ret;
      mo::rollback(check);
      v.pop_back();
    }
    for (int i = R; i <= n && !v.empty(); ++i) {
      mo::add(a[i], i);
      while (!v.empty() && r[v.back()] == i) {
        int id = v.back(), check = mo::history.size();
        for (int j = l[id]; j < R; ++j) mo::add(a[j], j);
        ret[id] = mo::ret;
        mo::rollback(check);
        v.pop_back();
      }
    }
  }
  for (int i = 0; i < m; ++i) {
    printf("%d\n", ret[i]);
  }
  return 0;
}

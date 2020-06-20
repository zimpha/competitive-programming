#include <cstdio>

#include <vector>
#include <algorithm>

const int inf = 2e9 + 10;

template <class T>
class DynamicRMQ {
public:
  void init(int n, int w) {
    u.assign(n * 2, w);
  }
  void modify(int p, const T& v) {
    for (u[p += u.size() / 2] = v; p > 1; p >>= 1) {
      u[p >> 1] = std::max(u[p], u[p ^ 1]);
    }
  }
  T query(int l, int r, T res = T()) {// [l, r)
    const int n = u.size() >> 1;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1) res = std::max(res, u[l++]);
      if (r & 1) res = std::max(res, u[--r]);
    }
    return res;
  }
private:
  std::vector<T> u;
};

DynamicRMQ<int> rmq;

int main() {
  int n, q;
  scanf("%d%d", &n, &q);
  std::vector<int> cx(n), xs(n), cy(n);
  std::vector<std::pair<int, int>> events;
  events.reserve(n * 2);
  for (int i = 0, r; i < n; ++i) {
    scanf("%d%d%d", &cx[i], &cy[i], &r);
    events.emplace_back(cy[i] - r, i + 1);
    events.emplace_back(cy[i] + r + 1, -i - 1);
    xs[i] = cx[i]; cy[i] += r;
  }
  std::vector<int> px(q), qx(q), ym(q), ret(q, 1);
  std::vector<std::pair<int, int>> q_events(q);
  for (int i = 0; i < q; ++i) {
    scanf("%d%*d%d%*d%d%d", &px[i], &qx[i], &q_events[i].first, &ym[i]);
    if (px[i] > qx[i]) std::swap(px[i], qx[i]);
    q_events[i].second = i;
  }
  std::sort(xs.begin(), xs.end());
  xs.erase(std::unique(xs.begin(), xs.end()), xs.end());
  for (int i = 0; i < n; ++i) {
    cx[i] = std::lower_bound(xs.begin(), xs.end(), cx[i]) - xs.begin();
  }
  rmq.init(xs.size(), -inf);
  std::sort(events.begin(), events.end());
  std::sort(q_events.begin(), q_events.end());
  for (int i = 0, j = 0; i < q; ++i) {
    for (; j < n * 2 && events[j].first <= q_events[i].first; ++j) {
      int e = std::abs(events[j].second) - 1;
      if (events[j].second > 0) rmq.modify(cx[e], cy[e]);
      else rmq.modify(cx[e], -inf);
    }
    int e = q_events[i].second;
    int l = std::lower_bound(xs.begin(), xs.end(), px[e]) - xs.begin();
    int r = std::upper_bound(xs.begin(), xs.end(), qx[e]) - xs.begin();
    int y = rmq.query(l, r, -inf);
    if (y >= ym[e]) ret[e] = 0;
  }
  for (int i = 0; i < q; ++i) {
    if (ret[i]) puts("YES");
    else puts("NO");
  }
  return 0;
}

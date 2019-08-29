#include <cstdio>
#include <vector>
#include <algorithm>

struct Event {
  int x, y1, y2, op;
};

int main() {
  int n, q;
  scanf("%d", &n);
  std::vector<int> ys;
  std::vector<Event> es;
  for (int i = 0; i < n; ++i) {
    int x1, y1, x2, y2;
    scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
    x1 *= 2, x2 *= 2, y1 *= 2, y2 *= 2;
    es.emplace_back();
    es.back().x = x1, es.back().y1 = y1, es.back().y2 = y2, es.back().op = +1;
    es.emplace_back();
    es.back().x = x2 + 1, es.back().y1 = y1, es.back().y2 = y2, es.back().op = -1;
    ys.push_back(y1); ys.push_back(y2);
  }
  scanf("%d", &q);
  std::vector<int> cnt(q), valid(q);
  for (int i = 0; i < q; ++i) {
    int x1, y1, x2, y2;
    scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
    int xm = x1 + x2, ym = y1 + y2;
    x1 *= 2, x2 *= 2, y1 *= 2, y2 *= 2;
    es.emplace_back();
    es.back().x = x1, es.back().y1 = y1, es.back().y2 = i, es.back().op = 2;
    es.emplace_back();
    es.back().x = x1, es.back().y1 = y2, es.back().y2 = i, es.back().op = 2;
    es.emplace_back();
    es.back().x = x2, es.back().y1 = y1, es.back().y2 = i, es.back().op = 2;
    es.emplace_back();
    es.back().x = x2, es.back().y1 = y2, es.back().y2 = i, es.back().op = 2;
    es.emplace_back();
    es.back().x = xm, es.back().y1 = ym, es.back().y2 = i, es.back().op = 3;
    ys.push_back(y1); ys.push_back(y2); ys.emplace_back(ym);
  }
  std::sort(es.begin(), es.end(), [](const Event &a, const Event &b) {
    return a.x < b.x || (a.x == b.x && a.op < b.op);
  });
  std::sort(ys.begin(), ys.end());
  ys.erase(std::unique(ys.begin(), ys.end()), ys.end());
  int m = ys.size();
  std::vector<int> bs(m);
  auto add = [&] (int x, int v) {
    for (; x < m; x += ~x & x + 1) bs[x] += v;
  };
  auto get = [&] (int x, int r = 0) {
    for (; x >= 0; x -= ~x & x + 1) r += bs[x];
    return r;
  };
  for (auto &e: es) {
    if (e.op == 1 || e.op == -1) {
      int l = std::lower_bound(ys.begin(), ys.end(), e.y1) - ys.begin();
      int r = std::lower_bound(ys.begin(), ys.end(), e.y2) - ys.begin();
      add(l, e.op); add(r + 1, -e.op);
    } else {
      int y = std::lower_bound(ys.begin(), ys.end(), e.y1) - ys.begin();
      if (get(y)) {
        if (e.op == 2) cnt[e.y2]++;
        else valid[e.y2] = 1;
      }
    }
  }
  for (int i = 0; i < q; ++i) {
    if (valid[i] || cnt[i] >= 3) puts("TAK");
    else puts("NIE");
  }
  return 0;
}

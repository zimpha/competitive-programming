#include <cstdio>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

int main() {
  int n, m;
  scanf("%d", &n);
  std::map<int, std::vector<std::pair<int, int>>> go;
  std::set<int> targets;
  int src;
  for (int i = 0; i < n; ++i) {
    int x, l, r;
    scanf("%d%d%d", &x, &l, &r);
    go[x].emplace_back(l, r);
    if (i == 0) src = x;
    targets.insert(x);
  }
  scanf("%d", &m);
  std::vector<int> y(m);
  for (int i = 0; i < m; ++i) {
    scanf("%d", &y[i]);
    targets.insert(y[i]);
  }
  std::map<int, int> dis = {{src, 0}};
  if (targets.count(src)) targets.erase(src);

  std::vector<int> queue = {src};
  auto relax = [&](int l, int r, int d) {
    auto it = targets.lower_bound(l);
    for (; it != targets.end(); ) {
      if (*it > r) break;
      dis[*it] = d;
      queue.push_back(*it);
      it = targets.erase(it);
    }
  };

  for (size_t i = 0; i < queue.size(); ++i) {
    int x = queue[i];
    for (auto &e: go[x]) {
      relax(x + e.first, x + e.second, dis[x] + 1);
      relax(x - e.second, x - e.first, dis[x] + 1);
    }
  }
  for (auto &x: y) {
    if (dis.count(x)) printf("%d ", dis[x]);
    else printf("-1 ");
  }
  puts("");
  return 0;
}

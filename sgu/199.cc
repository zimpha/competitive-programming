#include <cstdio>
#include <utility>
#include <vector>
#include <algorithm>

int main() {
  int n;
  scanf("%d", &n);
  std::vector<std::pair<int, int>> a(n);
  std::vector<int> id(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d%d", &a[i].first, &a[i].second);
    id[i] = i;
  }
  std::sort(id.begin(), id.end(), [&](int x, int y) {
    return a[x].first < a[y].first || (a[x].first == a[y].first && a[x].second > a[y].second);
  });
  std::vector<int> prev(n, -1);
  std::vector<std::pair<int, int>> g = {{0, -1}};
  for (int i = 0; i < n; ++i) {
    int v = a[id[i]].second;
    auto it = std::lower_bound(g.begin(), g.end(), std::pair<int, int>(v, -1));
    prev[id[i]] = (it - 1)->second;
    if (it == g.end()) {
      g.emplace_back(v, id[i]);
    } else {
      it->first = v;
      it->second = id[i];
    }
  }
  std::vector<int> res;
  printf("%d\n", (int)g.size() - 1);
  for (int u = g.back().second; u != -1; u = prev[u]) {
    res.push_back(u + 1);
  }
  for (auto &&v: res) printf("%d ", v);
  puts("");
  return 0;
}

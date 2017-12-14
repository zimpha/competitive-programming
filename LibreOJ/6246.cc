#include <cstdio>
#include <vector>
#include <algorithm>

using int64 = long long;

struct edge_t {
  int from, to, w;
  edge_t(int a, int b, int c): from(a), to(b), w(c) {}
};

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  scanf("%*d%*d%*d%*d%*d%*d");
  std::vector<int> h(m);
  for (int i = 0; i < m; ++i) {
    scanf("%d", &h[i]);
  }
  std::sort(h.begin(), h.end());
  std::vector<edge_t> edges;
  for (int i = 0; i < m; ++i) {
    edges.emplace_back(i + 1, i, 0);
  }
  for (int i = 0; i < n; ++i) {
    int k, x, p, c;
    scanf("%d%d%d%d", &k, &x, &p, &c);
    int l = std::lower_bound(h.begin(), h.end(), x - p) - h.begin();
    int r = std::upper_bound(h.begin(), h.end(), x + p) - h.begin();
    edges.emplace_back(r, l, c);
    if (k == 0) edges.emplace_back(l, r, -c);
  }
  std::vector<int64> dis(m + 1, -1);
  dis[m] = 0;
  for (int i = 0; i < m; ++i) {
    for (auto &&e: edges) {
      dis[e.to] = std::max(dis[e.to], dis[e.from] + e.w);
    }
  }
  bool update = false;
  for (auto &&e: edges) {
    if (dis[e.to] < dis[e.from] + e.w) update = true;
  }
  if (update) puts("No ANSWER");
  else printf("%lld\n", dis[0]);
  return 0;
}

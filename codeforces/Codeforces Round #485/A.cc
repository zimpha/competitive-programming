#include <cstdio>
#include <vector>
#include <queue>

int main() {
  int n, m, k, s;
  scanf("%d%d%d%d", &n, &m, &k, &s);
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }
  std::vector<std::vector<int>> edges(n);
  for (int i = 0; i < m; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    --u, --v;
    edges[u].push_back(v);
    edges[v].push_back(u);
  }
  std::vector<std::vector<int>> bucket(n);
  for (int x = 1; x <= k; ++x) {
    std::queue<int> queue;
    std::vector<int> dis(n, -1);
    for (int i = 0; i < n; ++i) {
      if (a[i] == x) {
        queue.push(i);
        dis[i] = 0;
      }
    }
    while (!queue.empty()) {
      int u = queue.front();
      bucket[dis[u]].emplace_back(u);
      queue.pop();
      for (auto &&v: edges[u]) if (dis[v] == -1) {
        dis[v] = dis[u] + 1;
        queue.emplace(v);
      }
    }
  }
  std::vector<int> ret(n), cnt(n);
  for (int i = 0; i < n; ++i) {
    for (auto &&u: bucket[i]) {
      if (cnt[u]++ < s) ret[u] += i;
    }
  }
  for (int i = 0; i < n; ++i) {
    if (i) putchar(' ');
    printf("%d", ret[i]);
  }
  puts("");
  return 0;
}

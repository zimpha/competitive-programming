#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  std::vector<std::vector<int>> edges(n);
  for (int i = 0; i < m; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    --u, --v;
    edges[u].push_back(v);
    edges[v].push_back(u);
  }
  std::vector<int> path = {0, edges[0][0]};
  std::vector<int> mark(n, 0);
  for (auto &&v: path) mark[v] = 1;
  for (size_t i = 0; i < path.size(); ) {
    int u = path[i], s = -1;
    for (auto &&v: edges[u]) if (mark[v] == 0) s = v;
    if (s == -1) {
      ++i;
      continue;
    }
    std::vector<int> from(n, -1);
    std::queue<int> queue;
    for (auto &&v: edges[u]) if (mark[v] == 0) {
      queue.push(v);
      from[v] = u;
    }
    mark[u] = -1;
    bool found = false;
    while (!queue.empty() && !found) {
      int x = queue.front();
      queue.pop();
      for (auto &&y: edges[x]) if (from[y] == -1) {
        if (mark[y] == 1) {
          std::vector<int> s;
          while (x != u) {
            mark[x] = 1;
            s.push_back(x);
            x = from[x];
          }
          std::reverse(s.begin(), s.end());
          path.insert(path.begin() + i + 1, s.begin(), s.end());
          found = true;
          break;
        } else if (mark[y] == 0) {
          queue.push(y);
          from[y] = x;
        }
      }
    }
    mark[u] = 1;
  }
  for (int i = 0; i < n; ++i) {
    if (i) putchar(' ');
    printf("%d", path[i] + 1);
  }
  puts("");
  std::reverse(path.begin() + 1, path.end());
  for (int i = 0; i < n; ++i) {
    if (i) putchar(' ');
    printf("%d", path[i] + 1);
  }
  puts("");
  return 0;
}

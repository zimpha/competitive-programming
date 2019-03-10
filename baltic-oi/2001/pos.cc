#include <cstdio>
#include <algorithm>
#include <functional>
#include <vector>

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  std::vector<int> head(n, -1), next(m * 2), to(m * 2);
  std::vector<int> w(n);
  int size = 0;
  for (int i = 0; i < n; ++i) scanf("%d", &w[i]);
  for (int i = 0; i < m; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    --u, --v;
    to[size] = v;
    next[size] = head[u];
    head[u] = size++;
    to[size] = u;
    next[size] = head[v];
    head[v] = size++;
  }
  std::vector<int> ret;
  std::vector<bool> mark(m * 2);
  std::function<void(int)> dfs = [&](int x) {
    for (int &i = head[x]; ~i; ) {
      if (mark[i]) {
        i = next[i];
        continue;
      }
      mark[i] = mark[i ^ 1] = 1;
      dfs(to[i]);
    }
    ret.push_back(x + 1);
  };
  dfs(0);
  printf("%d\n", m);
  for (auto &&x: ret) printf("%d ", x);
  puts("");
}

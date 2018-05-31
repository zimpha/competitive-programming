#include <cstdio>
#include <string>
#include <functional>
#include <vector>

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> a(n), b(n);
  std::vector<std::vector<int>> edges(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
    if (0 <= i + a[i] && i + a[i] < n) {
      edges[i + a[i]].emplace_back(i);
    }
  }
  for (int i = 0; i < n; ++i) {
    scanf("%d", &b[i]);
    if (0 <= i + b[i] && i + b[i] < n) {
      edges[i + b[i]].emplace_back(i);
    }
  }
  std::vector<bool> mark(n);
  std::function<void(int)> dfs = [&](int u) {
    if (mark[u]) return;
    mark[u] = 1;
    for (auto &&v: edges[u]) dfs(v);
  };
  dfs(n - 1);
  if (!mark[0]) {
    puts("No solution!");
    return 0;
  }
  std::string res;
  for (int i = 0, s = 0; i < n; ++i) {
    if (s == n - 1) break;
    if (0 <= s + a[s] && s + a[s] < n && mark[s + a[s]]) {
      s += a[s];
      res += 'a';
      continue;
    }
    s += b[s];
    res += 'b';
  }
  if (res.size() == n) puts("Infinity!");
  else puts(res.c_str());
  return 0;
}

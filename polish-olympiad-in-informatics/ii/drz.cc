#include <cstdio>
#include <vector>
#include <string>
#include <functional>

int main() {
  int n;
  scanf("%d", &n);
  std::vector<std::pair<int, int>> a(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i].first);
    a[i].second = i;
  }
  std::vector<int> l(n * 2 - 1, -1), r(n * 2 - 1, -1);
  std::vector<int> parent(n * 2 - 1);
  while (a.size() > 1) {
    int mx = 0;
    for (auto &&e: a) {
      mx = std::max(mx, e.first);
    }
    int idx = -1;
    for (int i = 0; i + 1 < a.size() && idx == -1; ++i) {
      if (a[i].first == mx && a[i + 1].first == mx) idx = i;
    }
    if (idx == -1) {
      puts("NIE");
      return 0;
    }
    l[n] = a[idx].second;
    r[n] = a[idx + 1].second;
    a[idx] = {mx - 1, n++};
    a.erase(a.begin() + idx + 1);
  }
  if (a[0].first != 0) {
    puts("NIE");
    return 0;
  }
  int idx = 0;
  std::function<std::string(int, int)> dfs = [&](int u, int p) -> std::string {
    int o = idx++;
    parent[o] = p;
    if (l[u] == -1 && r[u] == -1) return "()";
    std::string ret = "(";
    ret += dfs(l[u], o);
    ret += dfs(r[u], o);
    ret += ")";
    return ret;
  };
  auto ret = dfs(n - 1, -1);
  for (int i = 0; i < n; ++i) {
    if (i) putchar(' ');
    printf("%d", parent[i] + 1);
  }
  printf("\n%s\n", ret.c_str());
  return 0;
}

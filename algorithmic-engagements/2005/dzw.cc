#include <cstdio>
#include <vector>

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> p(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &p[i]);
    --p[i];
  }
  std::vector<std::vector<std::pair<int, int>>> ret;
  while (true) {
    std::vector<std::pair<int, int>> ops;
    std::vector<int> mark(n);
    for (int i = 0; i < n; ++i) {
      if (p[i] == i || mark[i]) continue;
      std::vector<int> c;
      for (int j = i; !mark[j]; j = p[j]) {
        c.push_back(j);
        mark[j] = 1;
      }
      for (int x = 0, y = c.size() - 1; x < y; ++x, --y) {
        std::swap(p[c[x]], p[c[y]]);
        ops.emplace_back(c[x] + 1, c[y] + 1);
      }
    }
    if (ops.empty()) break;
    ret.push_back(ops);
  }
  printf("%d\n", (int)ret.size());
  bool first = true;
  for (auto &ops: ret) {
    if (!first) puts("1");
    else first = false;
    for (auto &e: ops) {
      printf("%d %d\n", e.first, e.second);
    }
  }
  puts("2");
  return 0;
}

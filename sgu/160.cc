#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  std::vector<bool> mark(m);
  std::vector<std::pair<int, int>> from(m);
  for (int i = 0; i < n; ++i) {
    int x;
    scanf("%d", &x);
    x %= m;
    for (int j = 1; j < m; ++j) {
      if (mark[j] && !mark[j * x % m] && from[j].second != i) {
        mark[j * x % m] = 1;
        from[j * x % m] = {j, i};
      }
    }
    if (!mark[x]) {
      mark[x] = 1;
      from[x] = {0, i};
    }
  }
  for (int i = m - 1; i >= 0; --i) if (mark[i]) {
    if (i == 0) puts("1");
    else printf("%d\n", i);
    std::vector<int> choose;
    for (int x = i; x != 0; x = from[x].first) {
      choose.push_back(from[x].second + 1);
    }
    std::sort(choose.begin(), choose.end());
    for (auto &&x: choose) printf("%d ", x);
    puts("");
    break;
  }
  return 0;
}

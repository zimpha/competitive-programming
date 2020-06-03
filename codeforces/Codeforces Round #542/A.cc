#include <cstdio>
#include <vector>
#include <algorithm>

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  std::vector<std::vector<int>> out(n);
  for (int i = 0; i < m; ++i) {
    int a, b;
    scanf("%d%d", &a, &b);
    --a, --b;
    if (a < b) out[a].push_back(b - a);
    else out[a].push_back(n - (a - b));
  }
  for (int i = 0; i < n; ++i) {
    std::sort(out[i].begin(), out[i].end());
  }
  for (int i = 0; i < n; ++i) {
    int ret = 0;
    for (int j = 0; j < n; ++j) if (!out[j].empty()) {
      ret = std::max<int>(ret, (i <= j ? j - i : n - i + j) + (out[j].size() - 1) * n + out[j][0]);
    }
    if (i) putchar(' ');
    printf("%d", ret);
  }
  puts("");
  return 0;
}

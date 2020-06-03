#include <cstdio>
#include <vector>
#include <algorithm>

int main() {
  int n;
  scanf("%d", &n);
  std::vector<std::pair<int, int>> deg(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &deg[i].first);
    deg[i].second = i + 1;
  }
  for (int i = 0; i < n; ++i) {
    std::sort(deg.begin() + i, deg.end(), [](const std::pair<int, int> &a, const std::pair<int, int> &b) {
      return a.first > b.first;
    });
    for (int j = 0; j < deg[i].first; ++j) {
      --deg[i + 1 + j].first;
      printf("%d %d\n", deg[i].second, deg[i + 1 + j].second);
    }
  }
  return 0;
}

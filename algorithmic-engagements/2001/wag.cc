#include <cstdio>
#include <vector>
#include <algorithm>

int main() {
  int n;
  scanf("%d", &n);
  std::vector<std::pair<int, int>> p(n);
  std::vector<int> idx(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d%d", &p[i].first, &p[i].second);
    idx[i] = i;
  }
  std::sort(idx.begin(), idx.end(), [&](int x, int y) {
      int a = p[x].first * 1024 / (1 << p[x].second);
      int b = p[y].first * 1024 / (1 << p[y].second);
      if (a != b) return a < b;
      else return p[x].first < p[y].first;
  });
  for (auto &&i: idx) {
    printf("%d %d\n", p[i].first, p[i].second);
  }
  return 0;
}

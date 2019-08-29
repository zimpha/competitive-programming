#include <cstdio>
#include <cassert>
#include <vector>
#include <queue>
#include <algorithm>

using int64 = long long;

const int64 inf = 1e18;

int main() {
  int t1, t2, m, n1, n2;
  scanf("%d%d%d%d%d", &t1, &t2, &m, &n1, &n2);
  std::vector<std::pair<int, int>> go(m * n1), back(m * n2);
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n1; ++j) scanf("%d", &go[i * n1 + j].first);
    for (int j = 0; j < n1; ++j) go[i * n1 + j].second = go[j].first;
    for (int j = 0; j < n2; ++j) scanf("%d", &back[i * n2 + j].first);
    for (int j = 0; j < n2; ++j) back[i * n2 + j].second = back[j].first;
  }
  int64 best = t2 - t1;
  for (int i = 0; i < m; ++i) {
    std::sort(go.begin() + i * n1, go.begin() + (i + 1) * n1);
    std::sort(back.begin() + i * n2, back.begin() + (i + 1) * n2);
    std::vector<int64> mx(n2, inf);
    for (int j = n2 - 1; j >= 0; --j) {
      if (back[i * n2 + j].second <= t2) mx[j] = t2 - back[i * n2 + j].second + back[i * n2 + j].first;
      if (j + 1 < n2) mx[j] = std::min(mx[j], mx[j + 1]);
    }
    for (int j1 = 0, j2 = 0; j1 < n1 && j2 < n2; ++j1) {
      while (j2 < n2 && back[i * n2 + j2].first < go[i * n1 + j1].first) ++j2;
      if (j2 < n2 && go[i * n1 + j1].second >= t1 && mx[j2] != inf) {
        best = std::min(best, mx[j2] + go[i * n1 + j1].second - t1 - go[i * n1 + j1].first);
      }
    }
  }
  printf("%lld\n", best);
  return 0;
}

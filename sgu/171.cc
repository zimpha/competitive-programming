#include <cstdio>
#include <utility>
#include <algorithm>
#include <functional>
#include <vector>

using pii = std::pair<int, int>;

int main() {
  int m, n = 0;
  scanf("%d", &m);
  std::vector<pii> slot(m);
  for (int i = 0; i < m; ++i) {
    scanf("%d", &slot[i].second);
    n += slot[i].second;
  }
  for (int i = 0; i < m; ++i) {
    scanf("%d", &slot[i].first);
  }
  std::vector<pii> student(n);
  std::vector<int> id(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &student[i].second);
    id[i] = i;
  }
  for (int i = 0; i < n; ++i) {
    scanf("%d", &student[i].first);
  }
  std::sort(id.begin(), id.end(), [&](int x, int y) {
    return student[x].first > student[y].first || (student[x].first == student[y].first && student[x].second < student[y].second);
  });
  std::vector<int> ret(n);
  for (auto &&e: id) {
    auto &&s = student[e];
    int p = -1;
    for (int i = 0; i < m; ++i) if (slot[i].second && slot[i].first < s.second) {
      if (p == -1 || slot[p].first < slot[i].first) p = i;
    }
    if (p == -1) {
      for (int i = 0; i < m; ++i) if (slot[i].second) {
        if (p == -1 || slot[p].first < slot[i].first) {
          p = i;
        }
      }
    }
    --slot[p].second;
    ret[e] = p;
  }
  for (int i = 0; i < n; ++i) {
    if (i) putchar(' ');
    printf("%d", ret[i] + 1);
  }
  puts("");
  return 0;
}

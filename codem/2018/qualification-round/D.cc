#include <cstdio>
#include <vector>
#include <functional>
#include <algorithm>

int main() {
  int n, m, k, c;
  scanf("%d%d%d%d", &n, &m, &k, &c);
  std::vector<int> weight(m);
  for (int i = 0; i < m; ++i) {
    scanf("%d", &weight[i]);
  }
  std::vector<std::vector<int>> score(n, std::vector<int>(m));
  int x, y;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      scanf("%d", &score[i][j]);
      if (score[i][j] == -1) x = i, y = j;
    }
  }
  std::vector<int> count(n), mark(n);
  for (int it = 0; it <= c; ++it) {
    score[x][y] = it;
    std::vector<std::pair<long double, int>> rank(n);
    std::vector<int> top(m);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        top[j] = std::max(top[j], score[i][j]);
      }
    }
    for (int i = 0; i < n; ++i) {
      rank[i].second = i;
      for (int j = 0; j < m; ++j) {
        if (top[j] != 0) {
          rank[i].first += 1.0 * score[i][j] * weight[j] / top[j];
        }
      }
    }
    std::sort(rank.begin(), rank.end(), std::greater<std::pair<long double, int>>());
    if (k == n) {
      for (int i = 0; i < n; ++i) ++count[i];
      continue;
    }
    if (rank[k].first == rank[k - 1].first) {
      for (int i = 0; i < k; ++i) {
        if (rank[i].first > rank[k].first) ++count[rank[i].second];
      }
      for (int i = 0; i < n; ++i) {
        if (rank[i].first == rank[k].first) mark[rank[i].second] = 1;
      }
    } else {
      for (int i = 0; i < k; ++i) ++count[rank[i].second];
    }
  }
  for (int i = 0; i < n; ++i) {
    if (count[i] == c + 1) puts("1");
    else if (!count[i] && !mark[i]) puts("2");
    else puts("3");
  }
  return 0;
}

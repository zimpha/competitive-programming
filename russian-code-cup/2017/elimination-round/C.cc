#include <bits/stdc++.h>

using pii = std::pair<int, int>;

const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, k;
    scanf("%d%d", &n, &k);
    std::set<pii> all, mark;
    int x0, y0;
    for (int i = 0; i < n; ++i) {
      int x, y;
      scanf("%d%d", &x, &y);
      if (i == 0) x0 = x, y0 = y;
      all.emplace(x, y);
      if (x < x0) x0 = x, y0 = y;
    }
    printf("L %d\n", x0);
    std::vector<pii> ret(k - n);
    std::queue<pii> q;
    q.emplace(x0, y0);
    mark.emplace(x0, y0);
    for (int it = 0; it < k - n; ++it) {
      pii u = q.front();
      q.pop();
      ret[it] = u;
      for (int i = 0; i < 4; ++i) {
        int x = u.first + dx[i];
        int y = u.second + dy[i];
        if (all.count(pii(x, y)) && !mark.count(pii(x, y))) {
          mark.emplace(x, y);
          q.emplace(x, y);
        }
      }
    }
    for (auto &&e: all) {
      printf("%d %d\n", e.first, e.second);
    }
    for (auto &&e: ret) {
      printf("%d %d\n", x0 * 2 - e.first - 1, e.second);
    }
  }
  return 0;
}

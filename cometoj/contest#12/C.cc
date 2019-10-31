#include <cstdio>
#include <cassert>
#include <vector>
#include <queue>
#include <algorithm>

inline void update(int &x, int y) {
  if (x == -1 || x > y) x = y;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int s, t1, t2, m, n1, n2;
    scanf("%d%d%d%d%d%d", &m, &n1, &n2, &s, &t1, &t2);
    int n = n1 + n2;
    --s;
    std::vector<std::pair<int, int>> table;
    std::vector<int> pos(m * n, -1);
    std::vector<int> st(m), ed(m);
    table.reserve(m * n);
    for (int i = 0; i < m; ++i) {
      st[i] = table.size();
      for (int j = 0, t; j < n; ++j) {
        scanf("%d", &t);
        if (t1 <= t && t <= t2) table.emplace_back(t, i * n + j);
      }
      ed[i] = table.size();
      std::sort(table.begin() + st[i], table.begin() + ed[i]);
      for (int j = st[i]; j < ed[i]; ++j) {
        if (j == st[i] || table[j].first != table[j - 1].first) {
          pos[table[j].second] = j;
        } else {
          pos[table[j].second] = pos[table[j - 1].second];
        }
      }
    }
    std::vector<int> deg(table.size()), dp(table.size(), -1);
    for (int i = 0; i < m; ++i) {
      for (int j = st[i]; j < ed[i]; ++j) {
        if (j + 1 < ed[i]) deg[j + 1]++;
        int u = table[j].second % n;
        if (u < n1 && i + 1 < m && pos[(i + 1) * n + u] != -1) {
          deg[pos[(i + 1) * n + u]]++;
        }
        if (u >= n1 && i > 0 && pos[(i - 1) * n + u] != -1) {
          deg[pos[(i - 1) * n + u]]++;
        }
      }
    }
    if (st[s] < ed[s]) {
      dp[st[s]] = table[st[s]].first - t1;
    }
    std::queue<int> queue;
    for (size_t i = 0; i < table.size(); ++i) {
      if (deg[i] == 0) queue.push(i);
    }
    while (!queue.empty()) {
      int j = queue.front(); queue.pop();
      int i = table[j].second / n;
      int u = table[j].second % n;
      if (j + 1 < ed[i]) {
        if (dp[j] != -1) {
          update(dp[j + 1], dp[j] + table[j + 1].first - table[j].first);
        }
        if (--deg[j + 1] == 0) queue.push(j + 1);
      }
      int v = -1;
      if (u < n1 && i + 1 < m && pos[(i + 1) * n + u] != -1) {
        v = pos[(i + 1) * n + u];
      }
      if (u >= n1 && i > 0 && pos[(i - 1) * n + u] != -1) {
        v = pos[(i - 1) * n + u];
      }
      if (v != -1) {
        if (dp[j] != -1) {
          update(dp[v], dp[j]);
        }
        if (--deg[v] == 0) queue.push(v);
      }
    }
    int best = t2 - t1;
    for (int i = st[s]; i < ed[s]; ++i) if (dp[i] != -1) {
      update(best, dp[i] + t2 - table[i].first);
    }
    printf("%d\n", best);
  }
  return 0;
}

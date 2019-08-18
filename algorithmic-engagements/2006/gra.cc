#include <cstdio>
#include <cassert>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>

int main() {
  int n;
  scanf("%d", &n);
  std::vector<std::map<int, int>> dis(n * 2 + 1);
  std::vector<std::map<int, std::pair<int, int>>> pre(n * 2 + 1);
  std::queue<std::pair<int, int>> queue;
  queue.emplace(n, (1 << n) - 1);
  dis[n][(1 << n) - 1] = 0;
  while (!queue.empty()) {
    int p = queue.front().first;
    int s = queue.front().second;
    queue.pop();
    if (p == n && (s >> (n + 1)) == ((1 << n) - 1)) {
      printf("%d\n", dis[p][s]);
      std::vector<std::pair<int, int>> step;
      while (pre[p].count(s)) {
        step.emplace_back(p, s);
        auto e = pre[p][s];
        p = e.first;
        s = e.second;
      }
      std::reverse(step.begin(), step.end());
      for (auto &e: step) {
        int p = e.first, s = e.second;
        printf("%d ", p);
        for (int i = 0; i < p; ++i) {
          putchar('0' + (s >> i & 1));
        }
        putchar('_');
        for (int i = p + 1; i < n * 2 + 1; ++i) {
          putchar('0' + (s >> i & 1));
        }
        puts("");
      }
      break;
    }
    for (int d: {-2, -1, 1, 2}) {
      if (p + d < 0 || p + d >= n * 2 + 1) continue;
      int t = s, u = p + d;
      if (d == -2 || d == 2) {
        int v = (u + p) / 2;
        if ((t >> u & 1) != (t >> v & 1)) {
          if (t >> u & 1) {
            assert((t >> p & 1) == 0);
            t ^= 1 << p;
            t ^= 1 << u;
          }
        } else {
          u = p;
        }
      } else {
        if (t >> u & 1) {
          assert((t >> p & 1) == 0);
          t ^= 1 << p;
          t ^= 1 << u;
        }
      }
      if (!dis[u].count(t)) {
        pre[u][t] = {p, s};
        dis[u][t] = dis[p][s] + 1;
        queue.emplace(u, t);
      }
    }
  }
  return 0;
}

#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    if (n == 1) {
      puts("1");
      continue;
    }
    std::vector<std::pair<int, int>> prev(n, {-1, -1});
    std::queue<int> queue;

    prev[1 % n] = {0, 1};
    queue.emplace(1 % n);
    bool found = false;
    while (!queue.empty()) {
      int u = queue.front();
      queue.pop();
      if (u == 0) {
        std::vector<int> ret;
        while (true) {
          auto p = prev[u];
          ret.emplace_back(p.second);
          if (p.first == 0) break;
          u = p.first;
        }
        std::reverse(ret.begin(), ret.end());
        for (auto &&x: ret) putchar('0' + x);
        puts("");
        found = true;
        break;
      }
      if (prev[u * 10 % n].first == -1) {
        prev[u * 10 % n] = {u, 0};
        queue.emplace(u * 10 % n);
      }
      if (prev[(u * 10 + 1) % n].first == -1) {
        prev[(u * 10 + 1) % n] = {u, 1};
        queue.emplace((u * 10 + 1) % n);
      }
    }
    if (!found) {
      puts("BRAK");
    }
  }
  return 0;
}

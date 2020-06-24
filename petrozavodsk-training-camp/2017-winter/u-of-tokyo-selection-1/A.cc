#include <cstdio>
#include <vector>
#include <utility>

int main() {
  int n, k;
  scanf("%d%d", &n, &k);
  if (k > n / 2) puts("-1");
  else {
    std::vector<std::vector<std::pair<int, int>>> trees;
    trees.push_back(std::vector<std::pair<int, int>>{{1, 2}});
    int now = 2;
    for (; now + 2 <= n; now += 2) {
      int u = now + 1, v = now + 2;
      int cnt = 0;
      for (auto &&e: trees) {
        e.emplace_back(u, cnt + 1);
        e.emplace_back(v, now - cnt);
        ++cnt;
      }
      std::vector<std::pair<int, int>> new_tree = {{u, v}};
      for (int i = 1; i <= now / 2; ++i) {
        new_tree.emplace_back(v, i);
        new_tree.emplace_back(u, now - i + 1);
      }
      trees.push_back(new_tree);
    }
    if (n & 1) {
      int cnt = 1;
      for (auto &&e: trees) {
        e.emplace_back(n, cnt);
        ++cnt;
      }
    }
    for (int i = 0; i < k; ++i) {
      std::vector<std::pair<int, int>> &tree = trees[i];
      for (auto &&e: tree) {
        printf("%d %d\n", e.first, e.second);
      }
      puts("");
    }
  }
  return 0;
}

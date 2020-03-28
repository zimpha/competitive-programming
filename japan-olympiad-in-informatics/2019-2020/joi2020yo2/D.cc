#include <cstdio>
#include <cstring>
#include <queue>

const int N = 1e5 + 10;

int dp[10][N];
std::vector<int> go[10] = {
  {1},
  {0, 2, 4},
  {1, 3, 5},
  {2, 6},
  {1, 5, 7},
  {2, 4, 6, 8},
  {3, 5, 9},
  {4, 8},
  {5, 7, 9},
  {6, 8}
};

int main() {
  int m, r;
  scanf("%d%d", &m, &r);
  std::queue<std::pair<int, int>> queue;
  memset(dp, -1, sizeof(dp));
  queue.emplace(0, 0);
  dp[0][0] = 0;
  int ret = -1;
  while (!queue.empty()) {
    int p = queue.front().first;
    int v = queue.front().second;
    queue.pop();
    if (v == r) {
      ret = dp[p][r];
      break;
    }
    int u = (v * 10 + p) % m;
    if (dp[p][u] == -1) {
      dp[p][u] = dp[p][v] + 1;
      queue.emplace(p, u);
    }
    for (auto d: go[p]) {
      if (dp[d][v] == -1) {
        dp[d][v] = dp[p][v] + 1;
        queue.emplace(d, v);
      }
    }
  }
  printf("%d\n", ret);
  return 0;
}

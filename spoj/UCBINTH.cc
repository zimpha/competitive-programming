#include <cstdio>
#include <vector>
#include <queue>

const int N = 2e5;

std::vector<int> edges[N][2];

int main() {
  int n, k, m;
  scanf("%d%d%d", &n, &k, &m);
  for (int i = 0; i < m; ++i) {
    for (int j = 0, x; j < k; ++j) {
      scanf("%d", &x);
      --x;
      edges[i + n][1].push_back(x);
      edges[x][0].push_back(i + n);
    }
  }
  std::vector<int> queue[2];
  std::vector<int> dis(n + m, -1);
  queue[0].push_back(0);
  dis[0] = 1;
  for (int it = 0; !queue[it].empty(); it ^= 1) {
    queue[it ^ 1].clear();
    for (auto &&u: queue[it]) {
      for (auto &&v: edges[u][it]) {
        if (dis[v] == -1) {
          dis[v] = dis[u] + it;
          queue[it ^ 1].push_back(v);
        }
      }
    }
  }
  printf("%d\n", dis[n - 1]);
  return 0;
}

#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

using int64 = long long;

const int N = 5e5 + 10;

std::vector<std::pair<int, int>> edges[N];

int main() {
  int a, b, c, d, e, m;
  scanf("%d%d%d%d%d%d", &a, &b, &c, &d, &e, &m);
  std::vector<int> pos = {a, a + b, a + b + c, a + b + c + d};
  for (int i = 0; i < m; ++i) {
    int l, r;
    scanf("%d%d", &l, &r);
    --l;
    edges[l].emplace_back(r, r - l);
    edges[r].emplace_back(l, r - l);
  }
  int64 dis[4][4];
  memset(dis, -1, sizeof(dis));
  for (int i = 0; i < 4; ++i) {
    std::vector<int64> g(a + b + c + d + e + 1, -1);
    std::priority_queue<std::pair<int64, int>> pq;
    g[pos[i]] = 0;
    pq.emplace(0, pos[i]);
    while (!pq.empty()) {
      int64 d = -pq.top().first;
      int u = pq.top().second;
      pq.pop();
      if (g[u] != d) continue;
      for (auto &e: edges[u]) {
        int v = e.first;
        int64 w = d + e.second;
        if (g[v] == -1 || g[v] > w) {
          g[v] = w;
          pq.emplace(-g[v], v);
        }
      }
    }
    for (int j = 0; j < 4; ++j) dis[i][j] = g[pos[j]];
  }
  int64 ret = -1;
  if (dis[0][1] != -1 && dis[2][3] != -1) ret = dis[0][1] + dis[2][3];
  if (dis[0][2] != -1 && dis[1][3] != -1 && (ret == -1 || ret > dis[0][2] + dis[1][3])) {
    ret = dis[0][2] + dis[1][3];
  }
  if (dis[0][3] != -1 && dis[1][2] != -1 && (ret == -1 || ret > dis[0][3] + dis[1][2])) {
    ret = dis[0][3] + dis[1][2];
  }
  printf("%lld\n", ret);
  return 0;
}

#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

const int N = 1000 + 10, M = 120 * 20;

int dis[N][M][2];

struct Node {
  int u, sk, sc, va;
  bool operator < (const Node& rhs) const {
    return sc > rhs.sc;
  }
};

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  std::vector<int> ty(n), k(n), c(n);
  for (int i = 0; i < n; ++i) {
    char s[10];
    scanf("%s%d%d", s, &k[i], &c[i]);
    ty[i] = s[0] - 'A';
  }
  std::vector<std::vector<int>> go(n);
  std::vector<std::vector<std::pair<int, int>>> cost(n);
  for (int i = 0; i < m; ++i) {
    int u, v, k, c;
    scanf("%d%d%d%d", &u, &v, &k, &c);
    --u, --v;
    go[u].push_back(v); cost[u].emplace_back(k, c);
    go[v].push_back(u); cost[v].emplace_back(k, c);
  }
  int s, t;
  scanf("%d%d", &s, &t);
  --s, --t;
  memset(dis, -1, sizeof(dis));
  std::priority_queue<Node> pq;
  pq.push((Node){s, k[s], c[s], 0});
  dis[s][k[s]][0] = c[s];
  while (!pq.empty()) {
    auto node = pq.top();
    pq.pop();
    if (dis[node.u][node.sk][node.va] < node.sc) continue;
    for (size_t i = 0; i < go[node.u].size(); ++i) {
      int u = go[node.u][i];
      if (ty[u] == 2 && u != s && u != t) continue;
      int sk = node.sk + cost[node.u][i].first + k[u];
      int sc = node.sc + cost[node.u][i].second + c[u];
      int va = node.va | (ty[u] == 0);
      if (sk < M && (dis[u][sk][va] == -1 || dis[u][sk][va] > sc)) {
        dis[u][sk][va] = sc;
        pq.push((Node){u, sk, sc, va});
      }
    }
  }
  int best_c = -1;
  std::vector<std::pair<int, int>> ret;
  for (int i = 0; i < M; ++i) if (dis[t][i][1] != -1) {
    if (best_c == -1 || dis[t][i][1] < best_c) {
      best_c = dis[t][i][1];
      ret.emplace_back(i, best_c);
    }
  }
  printf("%d\n", (int)ret.size());
  for (auto &e: ret) {
    printf("%d %d\n", e.first, e.second);
  }
  return 0;
}

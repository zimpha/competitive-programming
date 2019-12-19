#include <cstdio>
#include <vector>
#include <queue>

const int N = 1000 + 10;

std::vector<std::pair<int, int>> edges[N];

std::vector<int> sssp(int s, int n) {
  std::vector<int> dis(n, -1);
  std::priority_queue<std::pair<int, int>> pq;
  dis[s] = 0; pq.emplace(0, s);
  while (!pq.empty()) {
    int d = -pq.top().first;
    int u = pq.top().second;
    pq.pop();
    if (dis[u] < d) continue;
    for (auto &e: edges[u]) {
      int v = e.first, w = e.second + d;
      if (dis[v] == -1 || dis[v] > w) {
        dis[v] = w;
        pq.emplace(-w, v);
      }
    }
  }
  return dis;
}

int main() {
  freopen("pump.in", "r", stdin);
  freopen("pump.out", "w", stdout);
  int n, m;
  scanf("%d%d", &n, &m);
  std::vector<int> u(m), v(m), c(m), f(m);
  for (int i = 0; i < m; ++i) {
    scanf("%d%d%d%d", &u[i], &v[i], &c[i], &f[i]);
    --u[i], --v[i];
  }
  int x = 0, y = 1;
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) edges[j].clear();
    for (int j = 0; j < m; ++j) if (f[j] >= f[i]) {
      edges[u[j]].emplace_back(v[j], c[j]);
      edges[v[j]].emplace_back(u[j], c[j]);
    }
    auto da = sssp(u[i], n);
    auto db = sssp(v[i], n);
    int dis = -1;
    for (int it = 0; it < 2; ++it) {
      if (da[0] != -1 && db[n - 1] != -1) {
        if (dis == -1 || dis > da[0] + db[n - 1] + c[i]) dis = da[0] + db[n - 1] + c[i];
      }
      da.swap(db);
    }
    if (dis != -1) {
      if (x * dis < f[i] * y) x = f[i], y = dis;
    }
  }
  printf("%d\n", x * 1000000 / y);
  return 0;
}

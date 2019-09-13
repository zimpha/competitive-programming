#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using int64 = long long;
const int N = 50000 + 10;

std::vector<std::pair<int, int>> edges[N];
int64 f[N], g[N];
int deg[N];

void update(int64 &x, int64 y) {
  if (x < y) x = y;
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0, s; i < n; ++i) {
    scanf("%d", &s);
    edges[i].resize(s);
    for (int j = 0; j < s; ++j) {
      scanf("%d%d", &edges[i][j].first, &edges[i][j].second);
      --edges[i][j].first;
    }
    deg[edges[i][0].first]++;
  }

  std::vector<std::vector<int>> cycles;
  std::vector<int> queue;
  for (int i = 0; i < n; ++i) {
    if (!deg[i]) queue.push_back(i);
  }
  for (size_t i = 0; i < queue.size(); ++i) {
    if (--deg[edges[queue[i]][0].first] == 0) {
      queue.push_back(edges[queue[i]][0].first);
    }
  }
  for (int i = 0; i < n; ++i) if (deg[i] == 1) {
    cycles.emplace_back();
    for (int x = i; deg[x] == 1; x = edges[x][0].first) {
      cycles.back().push_back(x);
      deg[x] = 0;
    }
  }

  memset(f, -1, sizeof(f[0]) * n);
  f[0] = 0;
  int64 ret = -1;
  for (int it = 0; it <= m; ++it) {
    memset(deg, 0, sizeof(deg[0]) * n);
    for (int i = 0; i < n; ++i) ++deg[edges[i][0].first];
    queue.clear();
    for (int i = 0; i < n; ++i) {
      if (deg[i] == 0) queue.push_back(i);
    }
    for (size_t i = 0; i < queue.size(); ++i) {
      int u = queue[i], v = edges[u][0].first;
      if (f[u] != -1) update(f[v], f[u] + edges[u][0].second);
      if (--deg[v] == 0) queue.push_back(v);
    }
    memcpy(g, f, sizeof(f[0]) * n);
    for (auto &c: cycles) {
      int nc = c.size();
      int64 sum = 0;
      static std::pair<int64, int> queue[N * 2];
      int head = 0, tail = -1;
      for (int i = 0; i < nc * 2; ++i) {
        int u = c[i % nc];
        if (f[u] != -1) {
          int64 w = f[u] - sum;
          while (head <= tail && queue[tail].first <= w) --tail;
          queue[++tail] = {w, i};
        }
        if (i >= nc) {
          while (head <= tail && queue[head].second <= i - nc) ++head;
          if (head <= tail) update(g[u], queue[head].first + sum);
        }
        sum += edges[u][0].second;
      }
    }
    update(ret, g[n - 1]);
    if (it == m) break;
    memset(f, -1, sizeof(f[0]) * n);
    for (int i = 0; i < n; ++i) if (g[i] != -1) {
      for (auto &e: edges[i]) {
        update(f[e.first], g[i] + e.second);
      }
    }
  }
  printf("%lld\n", ret);
  return 0;
}

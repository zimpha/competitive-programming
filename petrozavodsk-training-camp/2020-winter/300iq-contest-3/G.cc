#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>

const int N = 1e5 + 10;

std::vector<int> edges[N], graph[N];
int dsu[N];
int n, m, k;

int get(int u) {
  if (dsu[u] != u) dsu[u] = get(dsu[u]);
  return dsu[u];
}

struct CentroidNode {
  std::vector<int> nodes;
  std::vector<int> special, best;
  std::vector<std::vector<int>> dist;
  void build(std::vector<std::pair<int, int>>& extra, std::vector<std::pair<int, int>> &tree, int *top, int root) {
    int n = nodes.size();
    std::sort(nodes.begin(), nodes.end());
    special = {root};
    for (int i = 0; i < n; ++i) graph[i].clear();
    for (auto &e: extra) {
      int u = e.first, v = e.second;
      if (top[u] != top[v]) {
        special.push_back(u);
        special.push_back(v);
      }
      u = std::lower_bound(nodes.begin(), nodes.end(), u) - nodes.begin();
      v = std::lower_bound(nodes.begin(), nodes.end(), v) - nodes.begin();
      graph[u].push_back(v); graph[v].push_back(u);
    }
    for (auto &e: tree) {
      int u = e.first, v = e.second;
      u = std::lower_bound(nodes.begin(), nodes.end(), u) - nodes.begin();
      v = std::lower_bound(nodes.begin(), nodes.end(), v) - nodes.begin();
      graph[u].push_back(v); graph[v].push_back(u);
    }
    std::sort(special.begin(), special.end());
    special.erase(std::unique(special.begin(), special.end()), special.end());
    best.assign(special.size(), N);
    dist.assign(special.size(), std::vector<int>(n, -1));
    for (size_t i = 0; i < special.size(); ++i) {
      int v = special[i];
      v = std::lower_bound(nodes.begin(), nodes.end(), v) - nodes.begin();
      bfs(v, dist[i]);
    }
  }
  void bfs(int u, std::vector<int> &dist) {
    int *queue = dsu;
    queue[0] = u; dist[u] = 0;
    for (int h = 0, t = 1; h < t; ++h) {
      int u = queue[h];
      for (auto &v: graph[u]) if (dist[v] == -1) {
        dist[v] = dist[u] + 1;
        queue[t++] = v;
      }
    }
  }
  void update(int x) {
    x = std::lower_bound(nodes.begin(), nodes.end(), x) - nodes.begin();
    for (size_t i = 0; i < special.size(); ++i) {
      if (best[i] > dist[i][x]) best[i] = dist[i][x];
    }
  }
  int query(int x) {
    x = std::lower_bound(nodes.begin(), nodes.end(), x) - nodes.begin();
    int ret = N;
    for (size_t i = 0; i < special.size(); ++i) {
      if (ret > best[i] + dist[i][x]) ret = best[i] + dist[i][x];
    }
    return ret;
  }
} nodes[N];

std::vector<int> entries[N];

namespace centroid {
int size[N], mark[N], top[N];
int root, total, mins;
std::vector<std::pair<int, int>> tree;

void get_center(int u, int p = -1) {
  int mx = 0; size[u] = 1;
  for (auto &v: edges[u]) if (v != p && !mark[v]) {
    get_center(v, u);
    size[u] += size[v];
    if (size[v] > mx) mx = size[v];
  }
  if (total - size[u] > mx) mx = total - size[u];
  if (mx < mins) mins = mx, root = u;
}

void get_dist(int u, int p = -1) {
  nodes[root].nodes.push_back(u);
  if (p == -1 || p == root) top[u] = u;
  else top[u] = top[p];
  entries[u].emplace_back(root);
  size[u] = 1;
  for (auto &v: edges[u]) if (v != p && !mark[v]) {
    tree.emplace_back(u, v);
    get_dist(v, u);
    size[u] += size[v];
  }
}

void work(int u, int tot, std::vector<std::pair<int, int>>& extra) {
  total = tot; mins = total * 2;
  get_center(u);
  mark[u = root] = true;
  nodes[root].nodes.reserve(tot);
  tree.clear();
  get_dist(root);
  nodes[root].build(extra, tree, top, root);
  std::map<int, std::vector<std::pair<int, int>>> go;
  for (auto &e: extra) {
    int u = e.first, v = e.second;
    if (top[u] != top[v]) continue;
    go[top[u]].emplace_back(u, v);
  }
  for (auto &v: edges[root]) if (!mark[v]) {
    work(v, size[v], go[v]);
  }
}
}

int main() {
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 0; i < n; ++i) dsu[i] = i;
  std::vector<std::pair<int, int>> extra;
  for (int i = 0; i < m; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    --u, --v;
    if (get(u) != get(v)) {
      edges[u].push_back(v);
      edges[v].push_back(u);
      dsu[get(u)] = get(v);
    } else {
      extra.emplace_back(u, v);
    }
  }
  centroid::work(0, n, extra);
  int q;
  scanf("%d", &q);
  for (int i = 0; i < q; ++i) {
    int t, u;
    scanf("%d%d", &t, &u);
    --u;
    if (t == 1) {
      for (auto &e: entries[u]) {
        nodes[e].update(u);
      }
    } else {
      int ret = N;
      for (auto &e: entries[u]) {
        ret = std::min(ret, nodes[e].query(u));
      }
      printf("%d\n", ret);
    }
  }
  return 0;
}

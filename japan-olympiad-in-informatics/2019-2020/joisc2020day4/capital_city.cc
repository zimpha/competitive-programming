#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <vector>

const int N = 2e5 + 10;

std::vector<int> edges[N], city[N];
int col[N], dsu[N];

int get(int x) {
  if (x != dsu[x]) dsu[x] = get(dsu[x]);
  return dsu[x];
}

namespace centroid {
int total, mins, root;
int mark[N], size[N], cnt[N];
int parent[N], visited[N];
int pts[N], m;

void get_center(int u, int p = -1) {
  pts[m++] = u;
  cnt[col[u]]++;
  parent[u] = p;
  int mx = 0; size[u] = 1;
  for (auto &v: edges[u]) if (v != p && !mark[v]) {
    get_center(v, u);
    size[u] += size[v];
    if (size[v] > mx) mx = size[v];
  }
  if (total - size[u] > mx) mx = total - size[u];
  if (mx < mins) mins = mx, root = u;
}

int merge() {
  for (int i = 0; i < m; ++i) {
    int x = pts[i];
    dsu[x] = x;
    visited[col[x]] = false;
  }
  std::vector<int> queue = {col[root]};
  visited[col[root]] = true;
  for (size_t i = 0; i < queue.size(); ++i) {
    int c = queue[i];
    if (cnt[c] != city[c].size()) return 1e9;
    for (auto &u: city[c]) {
      for (int x = get(u); x != root; x = get(x)) {
        if (!visited[col[x]]) queue.push_back(col[x]);
        visited[col[x]] = true;
        dsu[x] = parent[x];
      }
    }
  }
  return queue.size() - 1;
}

int work(int u, int tot) {
  total = tot; mins = tot * 2;
  m = 0;
  get_center(u);
  mark[u = root] = true;
  for (int i = 0; i < m; ++i) {
    cnt[col[pts[i]]] = 0;
  }
  m = 0;
  get_center(u);
  int ret = merge();
  for (auto &v: edges[u]) if (!mark[v]) {
    ret = std::min(ret, work(v, size[v]));
  }
  return ret;
}
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 1; i < n; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    --u, --v;
    edges[u].push_back(v);
    edges[v].push_back(u);
  }
  for (int i = 0; i < n; ++i) {
    scanf("%d", &col[i]);
    city[--col[i]].push_back(i);
  }
  int ret = centroid::work(0, n);
  printf("%d\n", ret);
  return 0;
}

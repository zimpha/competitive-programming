#include <cstdio>
#include <cassert>
#include <cstring>
#include <vector>
#include <algorithm>

const int N = 2e5 + 10, K = 20;
using int64 = long long;

std::vector<std::pair<int, int>> edges[N];
int n, m;

namespace centroid {
int val[K][N], buf[N * 2];
int size[N], mark[N];
int ms, root, total;
int st[N], ed[N], nv;

void init(int n) {
  for (int i = 0; i < n; ++i) mark[i] = 0;
}

void get_center(int u, int p = -1) {
  int mx = 0; size[u] = 1;
  for (auto &e: edges[u]) {
    int v = e.first;
    if (v == p || mark[v]) continue;
    get_center(v, u);
    size[u] += size[v];
    mx = std::max(mx, size[v]);
  }
  mx = std::max(mx, total - size[u]);
  if (mx < ms) ms = mx, root = u;
}

void dfs(int u, int p, int c, int* dis) {
  for (int i = 0; i < m; ++i) dis[i] -= 1;
  dis[c] += 2;
  for (int i = 0; i < m; ++i) val[i][nv] = dis[i];
  nv++;
  for (auto &e: edges[u]) {
    int v = e.first, w = e.second;
    if (v == p || mark[v]) continue;
    dfs(v, u, w, dis);
  }
  for (int i = 0; i < m; ++i) dis[i] += 1;
  dis[c] -= 2;
}

int64 count(int l, int r, int bound) {
  ++bound;
  int64 ret = 0;
  for (int x = 0; x < m; ++x) {
    int* sum = buf + N;
    for (int i = -bound; i <= bound; ++i) sum[i] = 0;
    for (int i = l; i < r; ++i) {
      assert(-bound <= val[x][i] && val[x][i] <= bound);
      if (val[x][i] > 0) --ret;
      sum[val[x][i]]++;
    }
    for (int i = bound - 1; i >= -bound; --i) {
      sum[i] += sum[i + 1];
    }
    for (int i = l; i < r; ++i) {
      assert(-bound <= 1 - val[x][i] && 1 - val[x][i] <= bound);
      ret += sum[1 - val[x][i]];
    }
  }
  assert(ret % 2 == 0);
  return ret / 2;
}

int64 work(int u, int tot) {
  ms = tot * 2, total = tot;
  get_center(u);
  mark[u = root] = 1;
  get_center(u);
  int dis[K];
  memset(dis, 0, sizeof(dis));
  nv = 0;
  for (auto &e: edges[u]) if (!mark[e.first]) {
    st[e.first] = nv;
    dfs(e.first, u, e.second, dis);
    ed[e.first] = nv;
  }
  int64 ret = count(0, nv, size[u]);
  for (int x = 0; x < m; ++x) {
    for (int i = 0; i < nv; ++i) {
      ret += val[x][i] > 0;
    }
  }
  for (auto &e: edges[u]) if (!mark[e.first]) {
    ret -= count(st[e.first], ed[e.first], size[e.first]);
  }
  for (auto &e: edges[u]) if (!mark[e.first]) {
    ret += work(e.first, size[e.first]);
  }
  return ret;
}
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) edges[i].clear();
    for (int i = 1; i < n; ++i) {
      int u, v, w;
      scanf("%d%d%d", &u, &v, &w);
      --u, --v, --w;
      edges[u].emplace_back(v, w);
      edges[v].emplace_back(u, w);
    }
    centroid::init(n);
    int64 ret = (int64)n * (n - 1) / 2 - centroid::work(1, n);
    printf("%lld\n", ret);
  }
  return 0;
}

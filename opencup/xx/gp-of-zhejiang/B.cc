#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>

const int N = 2e5 + 10, M = 6e5 + 10;

std::vector<int> merge[N], query[N];
std::vector<int> edges[N];
int from[N], to[N], ret[M];

namespace centroid {
int size[N], mark[N], parent[N];
int total, mins, root;
int f[M], g[M];

int buffer[N], sz;

void get_center(int u, int p = -1) {
  int mx = 0; size[u] = 1;
  for (auto &e: edges[u]) {
    int v = from[e] + to[e] - u;
    if (v == p || mark[v]) continue;
    get_center(v, u);
    size[u] += size[v];
    if (mx < size[v]) mx = size[v];
  }
  if (mx < total - size[u]) mx = total - size[u];
  if (mx < mins) mins = mx, root = u;
}

void dfs(int u, int pe) {
  parent[u] = pe;
  buffer[sz++] = u; size[u] = 1;
  auto &mpe = merge[pe];
  for (auto &e: edges[u]) if (e != pe) {
    int v = from[e] + to[e] - u;
    if (mark[v]) continue;
    for (auto &ve: merge[e]) {
      auto it = std::lower_bound(mpe.begin(), mpe.end(), ve) - mpe.begin();
      if (it == mpe.size()) f[ve] = M;
      else f[ve] = f[mpe[it]];
      if (it == 0) g[ve] = -1;
      else g[ve] = g[mpe[it - 1]];
    }
    dfs(v, e);
    size[u] += size[v];
  }
}

int bit[M], now[N], m;

void add(int x, int v) {
  for (; x >= 0; x -= ~x & x + 1) bit[x] += v;
}

int get(int x, int r = 0) {
  for (; x < m; x += ~x & x + 1) r += bit[x];
  return r;
}

template<int sign>
void count(int l, int r) {
  // for each (t, out, u), find number of distinct v, ev <= t, g[ve] >= out[u]
  std::vector<std::pair<int, int>> qs, ms;
  std::vector<int> xs;
  for (int i = l; i < r; ++i) {
    int u = buffer[i], out = M;
    if (u == root) out = 0;
    else {
      for (auto &e: merge[parent[u]]) {
        out = std::min(out, f[e]);
        if (g[e] != -1) {
          now[u] = -1;
          ms.emplace_back(e, u);
          xs.push_back(g[e]);
        }
      }
    }
    for (auto &t: query[u]) if (out <= t) {
      qs.emplace_back(t, out);
    }
  }
  std::sort(xs.begin(), xs.end());
  xs.erase(std::unique(xs.begin(), xs.end()), xs.end());
  m = xs.size();
  for (int i = 0; i < m; ++i) bit[i] = 0;
  std::sort(qs.begin(), qs.end());
  std::sort(ms.begin(), ms.end());
  for (size_t i = 0, j = 0; i < qs.size(); ++i) {
    int t = qs[i].first, out = qs[i].second;
    out = std::lower_bound(xs.begin(), xs.end(), out) - xs.begin();
    for (; j < ms.size() && ms[j].first <= t; ++j) {
      int v = ms[j].second, gv = g[ms[j].first];
      if (now[v] != -1) add(now[v], -1);
      now[v] = std::lower_bound(xs.begin(), xs.end(), gv) - xs.begin();
      add(now[v], 1);
    }
    ret[t] += sign * get(out);
    if (sign == 1) ret[t]++;
  }
}

void work(int u, int tot) {
  total = tot; mins = tot * 2;
  get_center(u);
  mark[u = root] = true;
  buffer[0] = u; sz = 1;
  for (auto &e: edges[u]) {
    int v = from[e] + to[e] - u;
    if (mark[v]) continue;
    int offset = sz;
    for (auto &ve: merge[e]) {
      f[ve] = g[ve] = ve;
    }
    dfs(v, e);
    count<-1>(offset, sz);
  }
  count<1>(0, sz);
  for (auto &e: edges[u]) {
    int v = from[e] + to[e] - u;
    if (mark[v]) continue;
    work(v, size[v]);
  }
}
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 1; i < n; ++i) {
    scanf("%d%d", &from[i], &to[i]);
    --from[i], --to[i];
    edges[from[i]].push_back(i);
    edges[to[i]].push_back(i);
  }

  for (int i = 0; i < m; ++i) {
    ret[i] = -1;
    int op, u;
    scanf("%d%d", &op, &u);
    if (op == 2) merge[u].push_back(i);
    else query[u - 1].push_back(i), ret[i] = 0;
  }
  centroid::work(0, n);
  for (int i = 0; i < m; ++i) {
    if (ret[i] != -1) printf("%d\n", ret[i]);
  }
  return 0;
}

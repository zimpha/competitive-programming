#include <cstdio>
#include <cassert>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using int64 = long long;

const int N = 1e5 + 10;
const int mod = 1e9 + 7;

void add(int &x, int y) {
  if ((x += y) >= mod) x -= mod;
}

std::vector<int> edges[N];
int64 a[N], b[N], d[N], x0;
int c[N], e[N];

int top[N], idx[N], belong[N], depth[N];
bool in_cycle[N], mark[N];
int64 xs[N], sum[N];
int n, m;

void dfs(int u, int root, int p = -1) {
  xs[m++] = a[u] + sum[u];
  mark[u] = true;
  top[u] = root;
  for (auto &v: edges[u]) if (v != p && !in_cycle[v]) {
    depth[v] = depth[u] + 1;
    sum[v] = sum[u] + d[v];
    dfs(v, root, u);
  }
}

namespace SegTreeP {
  const int M = N * 20;
  int idx[M], ls[M], rs[M], sz;
  void init() {
    idx[0] = -1;
    ls[0] = rs[0] = 0;
    sz = 1;
  }

  int ins(int o, int l, int r, int x, int v) {
    int p = sz++;
    ls[p] = ls[o]; rs[p] = rs[o];
    if (l + 1 == r) return idx[p] = v, p;
    int m = (l + r) >> 1;
    if (x < m) ls[p] = ins(ls[o], l, m, x, v);
    else rs[p] = ins(rs[o], m, r, x, v);
    return p;
  }

  int get(int o, int l, int r, int x) {
    if (l + 1 == r) return idx[o];
    int m = (l + r) >> 1;
    if (x < m) return get(ls[o], l, m, x);
    else return get(rs[o], m, r, x);
  }
}

int root[N];
std::map<std::pair<int64, int>, std::tuple<int64, int, int>> go;

void dfs2(int u, int p = -1) {
  int o = p == -1 ? 0 : root[p];
  int x = std::lower_bound(xs, xs + m, a[u] + sum[u]) - xs;
  root[u] = SegTreeP::ins(o, 0, m, x, u);
  for (auto &v: edges[u]) if (v != p && !in_cycle[v]) {
    dfs2(v, u);
  }
}

struct Cycle {
  std::vector<int64> sum;
  std::vector<int> path;
  std::vector<std::pair<int, int64>> query;

  void add_query(int v, int64 x) {
    query.emplace_back(v, x);
  }

  void solve() {
    int n = path.size();
    sum.resize(n * 2);
    for (int i = 1; i < n * 2; ++i) {
      sum[i] = sum[i - 1] + d[path[(i - 1) % n]];
    }
    auto L = std::abs(sum[n]);
    std::vector<int64> xs(n * 2), val(n * 2);
    for (int i = 0; i < n * 2; ++i) {
      val[i] = a[path[i % n]] - sum[i];
      xs[i] = L == 0 ? 0 : (val[i] % L + L) % L;
    }
    std::sort(xs.begin(), xs.end());
    xs.erase(std::unique(xs.begin(), xs.end()), xs.end());
    std::vector<int> belong(n * 2);
    for (int i = 0; i < n * 2; ++i) {
      if (L == 0) belong[i] = 0;
      else belong[i] = std::lower_bound(xs.begin(), xs.end(), (val[i] % L + L) % L) - xs.begin();
      if (sum[n] < 0) val[i] = -val[i];
    }
    std::vector<std::set<std::pair<int64, int>>> sets(xs.size());
    std::sort(query.begin(), query.end());
    for (int i = 0, j = 0, k = 0; i < n; ++i) {
      for (; j < i + n; ++j) sets[belong[j]].emplace(val[j], j);
      for (; k < (int)query.size() && query[k].first == i; ++k) {
        int v = query[k].first;
        int64 x = query[k].second;
        int64 w = L == 0 ? 0 : ((x - sum[v]) % L + L) % L;
        auto p = std::lower_bound(xs.begin(), xs.end(), w) - xs.begin();
        if (p == xs.size() || xs[p] != w) {
          go[{x, path[v]}] = std::make_tuple(-1, -1, -1);
          continue;
        }
        int64 val = sum[n] < 0 ? sum[v] - x : x - sum[v];
        auto it = sets[p].lower_bound({val, 0});
        if (it == sets[p].end() || (L == 0 && it->first != val)) {
          go[{x, path[v]}] = std::make_tuple(-1, -1, -1);
        } else {
          assert(it->first >= val);
          int u = path[it->second % n];
          int step = it->second - v + 1;
          if (L != 0) step += (it->first - val) / L % mod * n % mod;
          go[{x, path[v]}] = std::make_tuple(a[u] + b[u], c[u], step % mod);
        }
      }
      sets[belong[i]].erase({val[i], i});
    }
  }
};

std::vector<Cycle> cycles;

void prepare() {
  dfs(n, n);
  for (int i = 0; i <= n; ++i) belong[i] = idx[i] = -1;
  for (int i = 0, v; i < n; ++i) if (!mark[i]) {
    for (v = i; !mark[v]; v = e[v]) mark[v] = true;
    cycles.emplace_back();
    auto &cycle = cycles.back();
    for (; mark[v]; v = e[v]) {
      mark[v] = false;
      in_cycle[v] = true;
      idx[v] = cycle.path.size();
      belong[v] = cycles.size() - 1;
      cycle.path.push_back(v);
    }
    for (auto u: cycle.path) dfs(u, u);
  }
  std::sort(xs, xs + m);
  m = std::unique(xs, xs + m) - xs;
  SegTreeP::init();
  dfs2(n);
  for (auto &cycle: cycles) {
    for (auto u: cycle.path) dfs2(u);
  }
}


int main() {
  scanf("%d%lld", &n, &x0);
  std::vector<std::pair<int64, int>> from = {{x0, 0}};
  for (int i = 0; i < n; ++i) {
    scanf("%lld%lld%d%lld%d", &a[i], &b[i], &c[i], &d[i], &e[i]);
    --c[i], --e[i];
    from.emplace_back(a[i] + b[i], c[i]);
    edges[e[i]].push_back(i);
  }
  prepare();

  for (auto &e: from) {
    if (go.count(e)) continue;
    int64 x = e.first;
    int v = e.second, step = 0;
    int p = std::lower_bound(xs, xs + m, x + sum[v]) - xs;
    if (p < m && xs[p] == x + sum[v]) {
      int u = SegTreeP::get(root[v], 0, m, p);
      if (u == -1) {
        x += sum[v], step = depth[v], v = top[v];
      } else {
        step = depth[v] - depth[u] + 1;
        x = a[u] + b[u]; v = c[u];
      }
    } else {
      x += sum[v], step = depth[v], v = top[v];
    }
    go[e] = std::make_tuple(x, v, step);
    if (belong[v] != -1) cycles[belong[v]].add_query(idx[v], x);
  }

  for (auto &cycle: cycles) cycle.solve();

  std::vector<bool> visited(n + 1);
  int ret = 0, v = 0;
  while (v != n) {
    auto it = go.find({x0, v});
    if (it == go.end()) { ret = -1; break; }
    add(ret, std::get<2>(it->second));
    v = std::get<1>(it->second);
    x0 = std::get<0>(it->second);
    go.erase(it);
    if (v == -1) { ret = -1; break; }
  }
  printf("%d\n", ret);
  return 0;
}

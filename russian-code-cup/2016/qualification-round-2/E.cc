#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using ll = long long;

const int N = 100000 + 10, POW = 16;
std::vector<std::pair<int, int>> edges[N];
int fa[N][20], mae[N][20], dep[N];
ll dis[N];
int n, q;

namespace LCA {
  void build(int n) {
    for (int i = 1; (1 << i) <= n; ++i) {
      for (int j = 0; j < n; ++j) if (~fa[j][i - 1]) {
        fa[j][i] = fa[fa[j][i - 1]][i - 1];
        mae[j][i] = std::max(mae[j][i - 1], mae[fa[j][i - 1]][i - 1]);
      }
    }
  }
  int up(int u, int d) {
    for (int i = 0; d; ++i, d >>= 1) {
      if (d & 1) u = fa[u][i];
    }
    return u;
  }
  int ask(int u, int v) {
    if (dep[u] < dep[v]) std::swap(u, v);
    u = up(u, dep[u] - dep[v]);
    for (int i = POW; i >= 0; --i) {
      if (fa[u][i] == fa[v][i]) continue;
      u = fa[u][i];
      v = fa[v][i];
    }
    if (u != v) u = fa[u][0];
    return u;
  }
}

void dfs(int u, int p = -1) {
  memset(fa[u], -1, sizeof(fa[u]));
  fa[u][0] = p;
  for (auto &&e: edges[u]) {
    if (e.first == p) continue;
    dis[e.first] = dis[u] + e.second;
    dep[e.first] = dep[u] + 1;
    mae[e.first][0] = e.second;
    dfs(e.first, u);
  }
}

ll get_dis(int u, int v) {
  return dis[u] + dis[v] - 2 * dis[LCA::ask(u, v)];
}

int get_max(int x, int y) {
  int z = LCA::ask(x, y), ret = 0;
  for (int i = POW; i >= 0; --i) {
    if (fa[x][i] != -1 && dep[fa[x][i]] >= dep[z]) {
      ret = std::max(ret, mae[x][i]);
      x = fa[x][i];
    }
  }
  x = y;
  for (int i = POW; i >= 0; --i) {
    if (fa[x][i] != -1 && dep[fa[x][i]] >= dep[z]) {
      ret = std::max(ret, mae[x][i]);
      x = fa[x][i];
    }
  }
  return ret;
}

int closest(int s, int t, int u) {
  int ret = s, tf;
  ll d = get_dis(s, u), td;
  if ((td = get_dis(t, u)) < d) d = td, ret = t;
  if ((td = get_dis(tf = LCA::ask(s, t), u)) < d) d = td, ret = tf;
  tf = LCA::ask(s, u);
  if (get_dis(s, tf) + get_dis(t, tf) == get_dis(s, t)) {
    if ((td = dis[u] - dis[tf]) < d) d = td, ret = tf;
  }
  tf = LCA::ask(t, u);
  if (get_dis(s, tf) + get_dis(t, tf) == get_dis(s, t)) {
    if ((td = dis[u] - dis[tf]) < d) d = td, ret = tf;
  }
  return ret;
}

bool on_edge(int x, int z, ll d) {
  for (int i = POW; i >= 0; --i) {
    if (fa[x][i] == -1 || dep[fa[x][i]] < dep[z]) continue;
    if (dis[x] - dis[fa[x][i]] <= d) {
      d -= dis[x] - dis[fa[x][i]];
      x = fa[x][i];
    }
  }
  return d != 0;
}

bool solve() {
  int b1, e1, s1;
  int b2, e2, s2;
  scanf("%d%d%d%d%d%d", &b1, &e1, &s1, &b2, &e2, &s2);
  --b1, --e1, --b2, --e2;
  int b = closest(b1, e1, b2);
  int e = closest(b1, e1, e2);
  if (b == e) return false;
  ll t2 = s2 + get_dis(b, b2), t1 = s1;
  ll db = get_dis(b, b1);
  ll de = get_dis(e, b1);
  int f = LCA::ask(b, e);
  if (db < de) {// same dir
    t1 += db;
    return std::abs(t1 - t2) < get_max(b, e);
  } else {
    t1 += de;
    ll d = dis[b] + dis[e] - 2 * dis[f] + t1 - t2;
    if (d <= 0 || d >= 2 * (dis[b] + dis[e] - 2 * dis[f])) return false;
    if (d & 1) return true;
    d /= 2;
    if (d == dis[b] - dis[f]) return false;
    if (d < dis[b] - dis[f]) return on_edge(b, f, d);
    else return on_edge(e, f, dis[b] + dis[e] - 2 * dis[f] - d);
  }
}

int main() {
  scanf("%d%d", &n, &q);
  for (int i = 1; i < n; ++i) {
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    edges[u - 1].emplace_back(v - 1, w);
    edges[v - 1].emplace_back(u - 1, w);
  }
  dfs(0);
  LCA::build(n);
  for (int i = 0; i < q; ++i) {
    if (solve()) puts("YES");
    else puts("NO");
  }
  return 0;
}

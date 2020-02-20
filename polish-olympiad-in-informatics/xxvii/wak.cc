#include <cstdio>
#include <cassert>
#include <cstring>
#include <vector>
#include <algorithm>

using int64 = long long;
using pii = std::pair<int64, int>;

const int N = 1e6 + 10;
const int64 inf = 1ll << 60;

std::vector<int> edges[N];
pii even[N], odd[N];
int64 w[N], sw[N];
int parent[N], depth[N];
int64 best;
int best_x, best_y;

void upd(int64 now, int x, int y) {
  if (now > best) {
    best = now, best_x = x, best_y = y;
  }
}

void dfs(int u, int p = -1) {
  pii o1 = {-inf, -1}, o2 = {-inf, -1};
  pii e1 = {-inf, -1}, e2 = {-inf, -1};
  odd[u] = {w[u], u}; even[u] = {-inf, -1};
  for (auto &v: edges[u]) if (v != p) {
    parent[v] = u;
    depth[v] = depth[u] + 1;
    dfs(v, u);
    odd[u] = std::max(odd[u], even[v]);
    even[u] = std::max(even[u], {odd[v].first + sw[u] - w[v], odd[v].second});
    pii o = {odd[v].first - w[v], odd[v].second};
    pii e = {even[v].first, even[v].second};
    if (o > o1) std::swap(o, o1);
    if (o > o2) std::swap(o, o2);
    if (e > e1) std::swap(e, e1);
    if (e > e2) std::swap(e, e2);
  }
  upd(odd[u].first, u, odd[u].second);
  // u as even node
  if (o2.first > -inf) upd(o1.first + o2.first + sw[u], o1.second, o2.second);
  // u as odd node
  if (e2.first > -inf) upd(e1.first + e2.first - w[u], e1.second, e2.second);
}

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) scanf("%lld", &w[i]);
  for (int i = 1; i < n; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    --u, --v;
    edges[u].push_back(v);
    edges[v].push_back(u);
  }
  for (int i = 0; i < n; ++i) {
    for (auto &j: edges[i]) sw[i] += w[j];
  }
  best = -inf;
  dfs(0);
  int x = best_x, y = best_y;
  if (depth[x] < depth[y]) std::swap(x, y);
  while (depth[x] > depth[y]) x = parent[x];
  while (x != y) x = parent[x], y = parent[y];
  std::vector<int> px, py;
  for (int u = best_x; u != x; u = parent[u]) px.push_back(u);
  for (int u = best_y; u != x; u = parent[u]) py.push_back(u);
  std::vector<int> path;
  for (auto &x: px) path.push_back(x);
  path.push_back(x);
  std::reverse(py.begin(), py.end());
  for (auto &x: py) path.push_back(x);
  assert(path.size() % 2 == 1);
  std::vector<int> ret;
  for (size_t i = 0; i + 1 < path.size(); i += 2) {
    ret.push_back(path[i]);
    ret.push_back(path[i + 1]);
    for (auto &x: edges[path[i + 1]]) {
      if (x != path[i] && x != path[i + 2]) {
        ret.push_back(x);
        ret.push_back(path[i + 1]);
      }
    }
  }
  ret.push_back(path.back());
  printf("%lld\n%d\n", best, int(ret.size() / 2) + 1);
  for (auto &x: ret) printf("%d ", x + 1);
  puts("");
  return 0;
}

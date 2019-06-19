#include <cstdio>
#include <vector>
#include <functional>
#include <algorithm>

const int N = 100;

struct lca {
  int x, y, z;
};

std::vector<int> edges[N];
std::vector<int> vs[N];
std::vector<lca> as[N];
int parent[N], deg[N], dsu[N];
int best[N];
int n, m;

std::vector<int> topo(const std::vector<int>& v, const std::vector<lca>& a) {
  for (auto &&u: v) {
    deg[u] = 0;
    edges[u].clear();
  }
  for (auto &&e: a) {
    if (e.z != e.x) {
      edges[e.z].push_back(e.x);
      deg[e.x]++;
    }
    if (e.z != e.y) {
      edges[e.z].push_back(e.y);
      deg[e.y]++;
    }
  }
  std::vector<int> queue;
  for (auto &&u: v) {
    if (deg[u] == 0) queue.push_back(u);
  }
  auto roots = queue;
  for (size_t i = 0; i < queue.size(); ++i) {
    int u = queue[i];
    for (auto &&v: edges[u]) {
      if (--deg[v] == 0) queue.push_back(v);
    }
  }
  if (queue.size() == v.size()) return roots;
  else return {};
}

int get(int x) {
    if (x != dsu[x]) dsu[x] = get(dsu[x]);
    return dsu[x];
}

void merge(int x, int y) {
  x = get(x), y = get(y);
  if (x != y) dsu[x] = y;
}

bool valid(int root, const std::vector<int> &v, const std::vector<lca> &a) {
  for (auto &&u: v) dsu[u] = u;
  for (auto &e: a) if (e.z != root) {
    merge(e.x, e.z);
    merge(e.y, e.z);
  }
  for (auto &e: a) if (e.z == root) {
    if (get(e.x) == get(e.y)) return false;
  }
  return true;
}

bool solve(const std::vector<int>& v, const std::vector<lca>& a, int p, int rest) {
  auto roots = topo(v, a);
  if (roots.empty()) return false;
  for (auto root: roots) {
    parent[root] = p;
    if (rest == 1) {
      for (int i = 0; i < n; ++i) best[i] = parent[i];
      return true;
    }
    if (!valid(root, v, a)) continue;
    for (auto &&u: v) {
      vs[u].clear();
      as[u].clear();
    }
    for (auto &&u: v) if (u != root) {
      vs[get(u)].push_back(u);
    }
    for (auto &&e: a) if (e.z != root) {
      as[get(e.z)].push_back(e);
    }
    std::vector<std::vector<int>> t_vs;
    std::vector<std::vector<lca>> t_as;
    for (auto &&u: v) if (!vs[u].empty()) {
      t_vs.emplace_back(std::move(vs[u]));
      t_as.emplace_back(std::move(as[u]));
    }
    bool valid = true;
    int t_rest = rest - 1;
    for (size_t i = 0; i < t_vs.size(); ++i) {
      valid &= solve(t_vs[i], t_as[i], root, t_rest);
      t_rest -= t_vs[i].size();
      if (!valid) break;
    }
    if (!valid) continue;
    else return true;
  }
  return false;
}

int ask_lca(int x, int y) {
  std::vector<int> a, b;
  for (; x != -1; x = parent[x]) a.push_back(x);
  for (; y != -1; y = parent[y]) b.push_back(y);
  std::reverse(a.begin(), a.end());
  std::reverse(b.begin(), b.end());
  int lca = -1;
  /*
     printf("lca(%d, %d):\n", x, y);
     for (auto &&x: a) printf("%d ", x);
     puts("");
     for (auto &&x: b) printf("%d ", x);
     puts("");*/
  for (size_t i = 0; i < a.size() && i < b.size(); ++i) {
    if (a[i] == b[i]) lca = a[i];
  }
  return lca;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    scanf("%d%d", &n, &m);
    std::vector<int> v(n);
    std::vector<lca> a(m);
    for (int i = 0; i < n; ++i) {
      v[i] = i;
      parent[i] = -1;
    }
    for (int i = 0; i < m; ++i) {
      scanf("%d%d%d", &a[i].x, &a[i].y, &a[i].z);
      --a[i].x;
      --a[i].y;
      --a[i].z;
    }

    auto check = [&] () {
      for (auto &&e: a) {
        if (ask_lca(e.x, e.y) != e.z) {
          printf("%d %d %d\n", e.x + 1, e.y + 1, e.z + 1);
          return false;
        }
      }
      return true;
    };

    if (!solve(v, a, -1, n)) {
      printf("Case #%d: Impossible\n", cas);
    } else {
      for (int i = 0; i < n; ++i) parent[i] = best[i];
      if (!check()) {
        puts("xxx");
      }
      printf("Case #%d:", cas);
      for (int i = 0; i < n; ++i) {
        printf(" %d", parent[i] + 1);
      }
      puts("");
    }
  }
  return 0;
}

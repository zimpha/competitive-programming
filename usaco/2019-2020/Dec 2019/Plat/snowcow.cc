#include <cstdio>
#include <cstdlib>
#include <vector>
#include <set>

using int64 = long long;

const int N = 1e5 + 10;

std::vector<int> edges[N];
std::set<std::pair<int, int>> col[N];
int st[N], ed[N], dfn;
int parent[N];
int size[N];

template<class T>
struct FenwickTree {
  T u[N * 2];
  int n;

  void init(int n) {
    this->n = n;
    for (int i = 0; i < n; ++i) u[i] = 0;
  }

  void add(int x, T v) {
    for (; x < n; x += ~x & x + 1) {
      u[x] += v;
    }
  }

  T get(int x, T r = 0) {
    for (; x >= 0; x -= ~x & x + 1) {
      r += u[x];
    }
    return r;
  }
};

void dfs(int u, int p = -1) {
  parent[u] = p;
  size[u] = 1;
  st[u] = dfn++;
  for (auto &v: edges[u]) if (v != p) {
    dfs(v, u);
    size[u] += size[v];
  }
  ed[u] = dfn++;
}

int main() {
  freopen("snowcow.in", "r", stdin);
  freopen("snowcow.out", "w", stdout);
  int n, q;
  scanf("%d%d", &n, &q);
  for (int i = 1; i < n; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    --u, --v;
    edges[u].push_back(v);
    edges[v].push_back(u);
  }
  dfs(0);
  FenwickTree<int> path;
  FenwickTree<int64> subtree;
  path.init(n * 2); subtree.init(n * 2);
  for (int i = 0; i < q; ++i) {
    int op, x, c;
    scanf("%d%d", &op, &x);
    --x;
    if (op == 1) {
      scanf("%d", &c);
      auto it = col[c].lower_bound(std::make_pair(st[x], x));
      bool add = true;
      for (; it != col[c].end(); ) {
        if (ed[it->second] <= ed[x]) {
          path.add(st[it->second], -1); path.add(ed[it->second] + 1, 1);
          subtree.add(st[it->second], -size[it->second]);
          it = col[c].erase(it);
        } else {
          break;
        }
      }
      it = col[c].lower_bound(std::make_pair(st[x], x));
      if (it != col[c].begin()) {
        --it;
        if (ed[it->second] >= ed[x]) add = false;
      }
      if (add) {
        col[c].emplace(st[x], x);
        path.add(st[x], 1); path.add(ed[x] + 1, -1);
        subtree.add(st[x], size[x]);
      }
    } else {
      int64 ret = subtree.get(ed[x]) - subtree.get(st[x] - 1);
      if (x) ret += (int64)path.get(st[parent[x]]) * size[x];
      printf("%lld\n", ret);
    }
  }
  return 0;
}

#include <vector>
#include <cassert>
#include <ctime>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <set>
#include <map>

static const int N = 10000 + 10; // 最大结点个数

std::vector<std::pair<int, int>> ret;

class Articulation {
public:
  std::set<int> forbid[N];
  std::vector<std::pair<int, int>> key;
  int col[N], cnt = 0, n;
  std::set<int> visited;
  // 传入结点个数n及各结点的出边e[]，返回双连通分量的个数cnt
  void run(int n, const std::vector<int> edges[]){
    this->n = n;
    memset(dfn, cnt = 0, sizeof(dfn[0]) * n);
    memset(low, 0, sizeof(low[0]) * n);
    for(int i = 0; i < n; ++i) {
      if(!dfn[i]) dfs(i, 1, edges);
    }
    memset(col, -1, sizeof(col[0]) * n);
    for (int i = 0; i < n; ++i) {
      if (col[i] == -1) find_cc(i, cnt++, edges);
    }
  }
private:
  int dfn[N], low[N];
  void find_cc(int x, int c, const std::vector<int> edges[], int p = -1) {
    col[x] = c;
    for (auto &y: edges[x]) if (y != p && !forbid[x].count(y)) {
      int a = x, b = y;
      if (a < b) std::swap(a, b);
      if (visited.count(a * n + b)) continue;
      visited.insert(a * n + b);
      ret.emplace_back(x, y);
      if (col[y] == -1) find_cc(y, c, edges, x);
    }
  }
  void dfs(int x, int dep, const std::vector<int> edges[]){
    int src = 0;
    dfn[x] = low[x] = dep;
    for (auto &y: edges[x]) {
      if (!dfn[y]){
        dfs(y, dep + 1, edges);
        low[x] = std::min(low[x], low[y]);
        if (low[y] > dfn[x]) {
          key.emplace_back(x, y);
          forbid[x].insert(y);
          forbid[y].insert(x);
        }
      } else if (dfn[y] != dfn[x] - 1 || src++){
        low[x] = std::min(low[x], dfn[y]);
      }
    }
  }
} tarjan;

std::vector<int> edges[N], gg[N];

// Schieber-Vishkin algorithm of LCA in O(n) ~ O(1)
class SchieberVishkinLCA {
public:
  // order[]: preorder of the vertex in the tree
  // parents[]: direct parent of vertex
  // root: root of the tree
  void build(int n, int *order, int * parents, int root) {
    indices.resize(n);
    ascendant.resize(n);
    head.resize(n);

    for (int i = 0; i < n; ++i) indices[order[i]] = i + 1;
    inlabel.assign(indices.begin(), indices.end());
    for (int i = n - 1; i > 0; --i) {
      int v = order[i], p = parents[v];
      if (lowbit(inlabel[p]) < lowbit(inlabel[v])) {
        inlabel[p] = inlabel[v];
      }
    }

    ascendant[root] = 0;
    for (int i = 1; i < n; ++i) {
      int v = order[i], p = parents[v];
      ascendant[v] = ascendant[p] | lowbit(inlabel[v]);
    }

    head[0] = root;
    for (int i = 1; i < n; ++i) {
      int v = order[i], p = parents[v];
      if (inlabel[v] != inlabel[p]) head[indices[v] - 1] = p;
      else head[indices[v] - 1] = head[indices[p] - 1];
    }
  }

  // return the LCA of u and v in O(1)
  int query(int u, int v) const {
    uint Iv = inlabel[v], Iu = inlabel[u];
    uint hIv = lowbit(Iv), hIu = lowbit(Iu);
    uint mask = highbit((Iv ^ Iu) | hIv | hIu);
    uint j = lowbit(ascendant[v] & ascendant[u] & ~mask);
    int x, y;
    if (j == hIv) x = v;
    else {
      mask = highbit(ascendant[v] & (j - 1));
      x = head[(indices[v] & ~mask | (mask + 1)) - 1];
    }
    if (j == hIu) y = u;
    else {
      mask = highbit(ascendant[u] & (j - 1));
      y = head[(indices[u] & ~mask | (mask + 1)) - 1];
    }
    return indices[x] < indices[y] ? x : y;
  }

private:
  using uint = unsigned int;
  static uint lowbit(uint x) { return x & (~x + 1); }
  static uint highbit(uint x) {
    x |= x >> 1; x |= x >> 2; x |= x >> 4; x |= x >> 8; x |= x >> 16;
    return x >> 1;
  }

  std::vector<uint> indices;
  std::vector<uint> inlabel;
  std::vector<uint> ascendant;
  std::vector<int> head;
} lca;

int order[N], parent[N], sz;
int up[N], down[N];

void dfs(int u, int p = -1) {
  order[sz++] = u;
  parent[u] = p;
  for (auto &v: gg[u]) if (v != p) {
    dfs(v, u);
  }
}

void dfs2(int u, int p = -1) {
  for (auto &v: gg[u]) if (v != p) {
    dfs2(v, u);
    up[u] += up[v];
    down[u] += down[v];
  }
}

int main() {
  srand(time(NULL));
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0, u, v; i < m; ++i) {
    scanf("%d%d", &u, &v);
    --u, --v;
    edges[u].push_back(v);
    edges[v].push_back(u);
  }
  tarjan.run(n, edges);
  std::map<int, int> mp;
  for (auto &e: tarjan.key) {
    int u = tarjan.col[e.first];
    int v = tarjan.col[e.second];
    mp[u * n + v] = e.first * n + e.second;
    mp[v * n + u] = e.second * n + e.first;
    assert(u != v);
    gg[u].push_back(v);
    gg[v].push_back(u);
  }
  sz = 0;
  dfs(0);
  lca.build(tarjan.cnt, order, parent, 0);
  int k;
  scanf("%d", &k);
  for (int i = 0; i < k; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    u = tarjan.col[u - 1];
    v = tarjan.col[v - 1];
    if (u == v) continue;
    int z = lca.query(u, v);
    up[u]++; up[z]--;
    down[v]++; down[z]--;
  }
  dfs2(0);
  for (int i = 1; i < tarjan.cnt; ++i) {
    int u = i, v = parent[i];
    if (up[i] != 0 && down[i] != 0) {
      puts("No");
      return 0;
    } else if (down[i]) {
      std::swap(u, v);
    }
    auto w = mp[u * n + v];
    ret.emplace_back(w / n, w % n);
  }
  puts("Yes");
  for (auto &e: ret) {
    printf("%d %d\n", e.first + 1, e.second + 1);
  }
  return 0;
}

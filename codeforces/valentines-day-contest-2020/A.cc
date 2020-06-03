#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

const int N = 4e5 + 10;
  
class Articulation {
public:
  typedef std::pair<int, int> PII;
  bool is_key[N];
  std::vector<int> cc[N], belong[N];
  int cnt;
  int run(int n, const std::vector<int> G[]){
    memset(dfn, use = 0, sizeof(dfn[0]) * n);
    memset(low, cnt = 0, sizeof(low[0]) * n);
    memset(is_key, 0, sizeof(is_key[0]) * n);
    fill_n(cc, n, std::vector<int>());
    fill_n(belong, n, std::vector<int>());
    for(int i = 0; i < n; ++i) {
      if(!dfn[i]) dfs(i, 1, G);
    }
    for (int i = 0; i < n; ++i) {
      for (auto &c: belong[i]) {
        cc[c].push_back(i);
      }
    }
    return cnt;
  }
private:
  int dfn[N], low[N], dot[N], use;
  void dfs(int x, int dep, const std::vector<int> G[]){
    int src = 0, out = 1 < dep;
    dot[use++] = x;
    dfn[x] = low[x] = dep;
    for (auto &y: G[x]) {
      if (!dfn[y]){
        dfs(y, dep + 1, G);
        low[x] = std::min(low[x], low[y]);
        if (low[y] >= dfn[x]){
          if (++out == 2) is_key[x] = 1;
          while (dot[--use] != y) belong[dot[use]].push_back(cnt);
          belong[x].push_back(cnt); 
          belong[y].push_back(cnt++);
        }
      } else if (dfn[y] != dfn[x] - 1 || src++){
        low[x] = std::min(low[x], dfn[y]);
      }
    }
  }
} tarjan;

// Schieber-Vishkin algorithm of LCA in O(n) ~ O(1)
class SchieberVishkinLCA {
public:
  // order[]: preorder of the vertex in the tree
  // parents[]: direct parent of vertex
  // root: root of the tree
  void build(int n, const int* order, int* parents, int root) {
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

std::vector<int> edges[N];
std::vector<int> tree[N];
int parent[N], order[N], sum[N];
int n, m;

void dfs(int u, int p = -1) {
  order[m++] = u;
  parent[u] = p;
  sum[u] += u < n;
  for (auto &v: tree[u]) if (v != p) {
    sum[v] = sum[u];
    dfs(v, u);
  }
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    --u, --v;
    edges[u].push_back(v);
    edges[v].push_back(u);
  }
  tarjan.run(n, edges);
  for (int i = 0; i < tarjan.cnt; ++i) {
    for (auto &v: tarjan.cc[i]) {
      tree[v].push_back(n + i);
      tree[n + i].push_back(v);
    }
  }

  m = 0;
  dfs(0);
  lca.build(n + tarjan.cnt, order, parent, 0);
  scanf("%d", &m);
  for (int i = 0; i < m; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    --u, --v;
    int z = lca.query(u, v);
    int ret = sum[u] + sum[v] - sum[z] - 2;
    if (parent[z] != -1) ret -= sum[parent[z]];
    printf("%d\n", ret);
  }
  return 0;
}

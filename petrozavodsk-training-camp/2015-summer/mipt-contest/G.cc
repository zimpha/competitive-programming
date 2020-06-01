#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>

// Schieber-Vishkin algorithm of LCA in O(n) ~ O(1)
class SchieberVishkinLCA {
public:
  // order[]: preorder of the vertex in the tree
  // parents[]: direct parent of vertex
  // root: root of the tree
  void build(int n, int *order, int* parents, int root) {
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

const int N = 1e5 + 10;

std::vector<int> edges[N];
int order[N], parent[N], sz;
double down[N], up[N];
double sum_down[N], sum_up[N];

void dfs(int u, int p = -1) {
  order[sz++] = u;
  parent[u] = p;
  up[u] = edges[u].size();
  for (auto &v: edges[u]) if (v != p) {
    dfs(v, u);
    up[u] += up[v];
  }
}

void dfs2(int u, int p = -1) {
  if (p != -1) {
    sum_up[u] = sum_up[p];
    sum_down[u] = sum_down[p];
  }
  for (auto &v: edges[u]) if (v != p) {
    down[v] = down[u] + up[u] - up[v];
  }
  sum_up[u] += up[u]; sum_down[u] += down[u];
  for (auto &v: edges[u]) if (v != p) dfs2(v, u);
}

int main() {
  int n, q;
  scanf("%d", &n);
  for (int i = 1; i < n; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    edges[u - 1].push_back(v - 1);
    edges[v - 1].push_back(u - 1);
  }
  dfs(0);
  lca.build(n, order, parent, 0);
  dfs2(0);
  scanf("%d", &q);
  for (int i = 0; i < q; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    --u, --v;
    int w = lca.query(u, v);
    printf("%.10f\n", sum_up[u] - sum_up[w] + sum_down[v] - sum_down[w]);
  }
  return 0;
}

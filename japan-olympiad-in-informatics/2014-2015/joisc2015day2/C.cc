#include <cstdio>
#include <vector>

const int N = 1e5 + 10;

class SchieberVishkinLCA {
public:
  // order[]: preorder of the vertex in the tree
  // parents[]: direct parent of vertex
  // root: root of the tree
  void build(int n, int order[], int parents[], int root) {
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
int parent[N], depth[N];
int dsu1[N], dsu2[N];
int order[N];
int st[N], ed[N], size;
int bit[N];

void add(int x, int v) {
  for (; x < size; x += ~x & x + 1) bit[x] += v;
}

int sum(int x, int r = 0) {
  for (; x >= 0; x -= ~x & x + 1) r += bit[x];
  return r;
}

int get(int* dsu, int x) {
  if (dsu[x] != x) dsu[x] = get(dsu, dsu[x]);
  return dsu[x];
}

void dfs(int u, int p = -1) {
  order[size] = u;
  st[u] = size++;
  for (auto &v: edges[u]) if (v != p) {
    parent[v] = u;
    depth[v] = depth[u] + 1;
    dfs(v, u);
  }
  ed[u] = size;
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  std::vector<int> type(m), a(m), b(m);
  for (int i = 0; i < n; ++i) dsu1[i] = i;
  for (int i = 0; i < m; ++i) {
    scanf("%d%d%d", &type[i], &a[i], &b[i]);
    --a[i], --b[i];
    if (type[i] == 1) {
      int u = get(dsu1, a[i]);
      int v = get(dsu1, b[i]);
      if (u != v) {
        edges[a[i]].push_back(b[i]);
        edges[b[i]].push_back(a[i]);
        dsu1[u] = v;
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    if (get(dsu1, i) == i) edges[n].push_back(i);
  }
  dfs(n);
  lca.build(n + 1, order, parent, n);
  for (int i = 0; i <= n; ++i) dsu1[i] = dsu2[i] = i;
  for (int i = 0; i < m; ++i) {
    int z = lca.query(a[i], b[i]);
    int u = get(dsu1, a[i]), v = get(dsu1, b[i]);
    if (type[i] == 1) {
      if (u != v) dsu1[u] = v;
      else {
        for (u = get(dsu2, a[i]); depth[u] > depth[z]; u = get(dsu2, parent[u])) {
          add(st[u], 1); add(ed[u], -1);
          dsu2[u] = parent[u];
        }
        for (v = get(dsu2, b[i]); depth[v] > depth[z]; v = get(dsu2, parent[v])) {
          add(st[v], 1); add(ed[v], -1);
          dsu2[v] = parent[v];
        }
      }
    } else {
      if (u != v) puts("-1");
      else {
        int su = sum(st[a[i]]);
        int sv = sum(st[b[i]]);
        int sz = sum(st[z]);
        printf("%d\n", depth[a[i]] + depth[b[i]] - 2 * depth[z] - (su + sv - sz * 2));
      }
    }
  }
  return 0;
}

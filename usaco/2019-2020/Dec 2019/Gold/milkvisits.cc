#include <cstdio>
#include <vector>

// Schieber-Vishkin algorithm of LCA in O(n) ~ O(1)
class SchieberVishkinLCA {
public:
  // order[]: preorder of the vertex in the tree
  // parents[]: direct parent of vertex
  // root: root of the tree
  void build(int n, int *order, int *parents, int root) {
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

namespace SegmentTree {
  struct Node {
    int l, r;
    int cnt;
  } T[N * 20];
  int sz;

  void init() {
    T[0].l = T[0].r = T[0].cnt = 0;
    sz = 1;
  }

  int ins(int o, int l, int r, int x) {
    int p = sz++;
    T[p] = T[o];
    T[p].cnt++;
    if (l + 1 == r) return p;
    int m = (l + r) >> 1;
    if (x < m) T[p].l = ins(T[p].l, l, m, x);
    else T[p].r = ins(T[p].r, m, r, x);
    return p;
  }
  int get(int o, int l, int r, int x) {
    if (l + 1 == r) return T[o].cnt;
    int m = (l + r) >> 1;
    if (x < m) return get(T[o].l, l, m, x);
    else return get(T[o].r, m, r, x);
  }
}

std::vector<int> edges[N];
int roots[N], order[N], parent[N], sz;
int type[N], n, m;

void dfs(int u, int o, int p = -1) {
  order[sz++] = u;
  parent[u] = p;
  roots[u] = SegmentTree::ins(o, 0, n, type[u] - 1);
  for (auto &v: edges[u]) {
    if (v != p) dfs(v, roots[u], u);
  }
}

int main() {
  freopen("milkvisits.in", "r", stdin);
  freopen("milkvisits.out", "w", stdout);
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) scanf("%d", &type[i]);
  for (int i = 1; i < n; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    edges[u - 1].emplace_back(v - 1);
    edges[v - 1].emplace_back(u - 1);
  }
  SegmentTree::init();
  dfs(0, 0);
  lca.build(n, order, parent, 0);
  for (int i = 0; i < m; ++i) {
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    --a, --b;
    int z = lca.query(a, b);
    int cnt = SegmentTree::get(roots[a], 0, n, c - 1) + SegmentTree::get(roots[b], 0, n, c - 1) - SegmentTree::get(roots[z], 0, n, c - 1) * 2 + (type[z] == c);
    putchar("01]"[cnt > 0]);
  }
  puts("");
  return 0;
}

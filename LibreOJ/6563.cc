#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

// Schieber-Vishkin algorithm of LCA in O(n) ~ O(1)
class SchieberVishkinLCA {
public:
  // order[]: preorder of the vertex in the tree
  // parents[]: direct parent of vertex
  // root: root of the tree
  void build(const std::vector<int> &order, const std::vector<int> &parents, int root) {
    const int n = order.size();
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

const int N = 2e5 + 10;

struct Node {
  Node *ch[2];
  int size;
} pool[N * 32], *ptr, *null;

std::vector<int> edges[N];
std::vector<int> order, parent, val;
std::vector<Node*> roots;

Node* insert(Node* o, int v) {
  Node *root = ptr++;
  Node *p = root;
  for (int i = 30; i >= 0; --i) {
    int b = v >> i & 1;
    p->size = o->size + 1;
    p->ch[b ^ 1] = o->ch[b ^ 1];
    p->ch[b] = ptr++;
    p = p->ch[b];
    o = o->ch[b];
  }
   p->size = o->size + 1;
  return root;
}

int query(Node *a, Node *b, int v) {
  int ret = 0;
  for (int i = 30; i >= 0; --i) {
    int o = (v >> i & 1) ^ 1;
    if (a->ch[o]->size > b->ch[o]->size) {
      ret ^= 1 << i;
      a = a->ch[o];
      b = b->ch[o];
    } else {
      a = a->ch[o ^ 1];
      b = b->ch[o ^ 1];
    }
  }
  return ret;
}

void dfs(int u, int p = -1) {
  roots[u] = insert(p == -1 ? null : roots[p], val[u]);
  if (p != -1) val[u] ^= val[p];
  parent[u] = p;
  order.push_back(u);
  for (auto &v: edges[u]) if (v != p) {
    dfs(v, u);
  }
}

int main() {
  int n, m, w;
  scanf("%d%d%d", &n, &m, &w);
  val.resize(n);
  for (int i = 1; i < n; ++i) {
    int x, y;
    scanf("%d%d", &x, &y);
    --x, --y;
    edges[x].push_back(y);
    edges[y].push_back(x);
  }
  for (int i = 0; i < n; ++i) scanf("%d", &val[i]);
  parent.resize(n);
  roots.resize(n);
  order.reserve(n);
  ptr = pool;
  null = ptr++;
  null->ch[0] = null->ch[1] = null;
  null->size = 0;
  dfs(0);
  lca.build(order, parent, 0);
  for (int i = 0; i < m; ++i) {
    int x, y, s;
    scanf("%d%d%d", &x, &y, &s);
    --x, --y;
    int z = lca.query(x, y);
    int mx = query(roots[x], roots[z], s);
    int val_z = (parent[z] == -1 ? val[z] : val[z] ^ val[parent[z]]);
    mx = std::max(mx, query(roots[y], roots[z], s));
    mx = std::max(mx, val_z ^ s);
    int ret = val[x] ^ val[y] ^ val_z ^ mx ^ s;
    int ans = 0;
    for (int i = 30; i >= 0; --i) {
      if ((ans | (1 << i)) > w) continue;
      if (ret >> i & 1) continue;
      ans ^= 1 << i;
    }
    printf("%d\n", ans | ret);
  }
  return 0;
}

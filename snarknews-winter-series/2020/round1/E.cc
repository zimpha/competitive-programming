#include <cstdio>
#include <vector>
#include <algorithm>
#include <functional>

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

const int N = 3e5 + 10;

std::vector<int> edges[N];
int order[N], parent[N];
int p[N], depth[N];
int n, m, k;

void dfs(int u, int p = -1) {
  parent[u] = p;
  order[m++] = u;
  for (auto &v: edges[u]) if (v != p) {
    depth[v] = depth[u] + 1;
    dfs(v, u);
  }
}

template <int opt(int, int)> struct ST {
  int u[N][20], n;
  int lg[N];
  void init() {
    lg[0] = -1;
    for (int i = 1; i < N; ++i) {
      lg[i] = lg[i >> 1] + 1;
    }
  }
  void build(int a[], int n) {
    this->n = n;
    for (int i = 0; i < n; ++i) u[i][0] = a[i];
    for (int j = 1; (1 << j) <= n; ++j) {
      for (int i = 0; i + (1 << j) <= n; ++i) {
        u[i][j] = opt(u[i][j- 1 ], u[i + (1 << (j - 1))][j - 1]);
      }
    }
  }
  int ask(int a, int b) {
    if (a > b) std::swap(a, b);
    int k = lg[b - a + 1];
    return opt(u[a][k], u[b - (1 << k) + 1][k]);
  }
};

int opt(int i, int j) {
  return lca.query(i, j);
}

ST<opt> st;
int dp[2][N];

int main() {
  st.init();
  scanf("%d%d", &n, &k);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &p[i]);
    --p[i];
  }
  for (int i = 1; i < n; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    --u, --v;
    edges[u].push_back(v);
    edges[v].push_back(u);
  }
  m = 0;
  depth[0] = 1;
  dfs(0);
  lca.build(n, order, parent, 0);
  st.build(p, n);
  for (int i = 0; i < n; ++i) {
    dp[1][i] = depth[st.ask(0, i)];
  }
  for (int i = 1; i < k; ++i) {
    int u = i & 1, v = u ^ 1;
    for (int j = 0; j < n; ++j) dp[v][j] = -1;

    std::function<void(int, int, int, int)> solve = [&] (int l, int r, int sl, int sr) {
      if (l > r) return;
      int m = (l + r) / 2, sm = -1;
      int best = -1;
      for (int j = sl; j <= sr && j < m; ++j) if (dp[u][j] != -1) {
        int now = dp[u][j] + depth[st.ask(j + 1, m)];
        if (best == -1 || now < best) best = now, sm = j;
      }
      if (sm == -1) sm = 0;
      solve(l, m - 1, sl, sm);
      dp[v][m] = best;
      solve(m + 1, r, sm, sr);
    };

    solve(0, n - 1, 0, n - 1);
  }
  printf("%d\n", dp[k & 1][n - 1]);
  return 0;
}

#include <cstdio>
#include <algorithm>
#include <cassert>
#include <vector>
#include <map>

using uint64 = unsigned long long;

const int N = 1e5 + 10;
const int seed = 1e9 + 9, mod = 1e9 + 7;

struct Tree {
  std::vector<std::vector<int>> edges;
  std::vector<uint64> hash;
  std::vector<int> depth, size;
  std::vector<int> parent;
  int n, root;
  Tree(): n(0) {}
  void init() {
    edges.assign(n, {});
    hash.resize(n, 0);
    depth.resize(n, 0);
    parent.resize(n, -1);
    size.resize(n, 0);
  }
  void build(int _n) {
    this->n = _n;
    init();
    for (int i = 0, p; i < n; ++i) {
      scanf("%d", &p);
      if (p == 0) root = i;
      else edges[p - 1].push_back(i);
      parent[i] = p - 1;
    }
    dfs(root);
  }
  void print() {
    parent[root] = -1;
    for (int i = 0; i < n; ++i) {
      for (auto &v: edges[i]) parent[v] = i;
    }
    for (int i = 0; i < n; ++i) {
      if (i) putchar(' ');
      printf("%d", parent[i] + 1);
    }
    puts("");
  }
  int leaf() const {
    int ret = 0;
    for (int i = 1; i < n; ++i) {
      if (depth[i] > depth[ret]) ret = i;
    }
    return ret;
  }
  int new_node() {
    edges.emplace_back();
    hash.emplace_back();
    depth.emplace_back();
    parent.emplace_back();
    size.emplace_back();
    return n++;
  }
  void dfs(int u) {
    hash[u] = 1;
    size[u] = 1;
    std::vector<uint64> hs;
    for (auto &v: edges[u]) {
      depth[v] = depth[u] + 1;
      dfs(v);
      hs.push_back(hash[v]);
      size[u] += size[v];
    }
    std::sort(hs.begin(), hs.end());
    for (auto &h: hs) {
      hash[u] = (hash[u] * seed + h + 1) % mod;
    }
    hash[u] %= mod;
  }
} A, B, C;

int build_from_subtree(const Tree &C, Tree &X, int u) {
  int now = X.new_node();
  for (auto &v: C.edges[u]) {
    int son = build_from_subtree(C, X, v);
    X.edges[now].push_back(son);
  }
  return now;
}

int mul(const Tree &A, const Tree &B, Tree &C, int u) {
  int now = build_from_subtree(B, C, B.root);
  for (auto &v: A.edges[u]) {
    int son = mul(A, B, C, v);
    C.edges[now].push_back(son);
  }
  return now;
}

bool solve(const Tree &A, const Tree &B, const Tree &C, bool reverse = false) {
  if (A.n + B.n - 1 > C.n) return false;
  int leaf_a = A.leaf(), leaf_c = C.leaf();
  int delta = C.depth[leaf_c] - A.depth[leaf_a];
  if (delta < 0) return false;
  int u = leaf_c;
  for (int i = 0; i < delta; ++i) u = C.parent[u];
  Tree X, Y, AX, BY;
  X.root = build_from_subtree(C, X, u);
  if ((uint64)X.n * A.n > C.n) return false;
  AX.root = mul(A, X, AX, A.root);
  assert(AX.n == A.n * X.n);

  AX.dfs(AX.root);
  std::map<uint64, std::vector<int>> hc;
  for (auto &v: C.edges[C.root]) {
    hc[C.hash[v]].push_back(v);
  }

  for (auto &v: AX.edges[AX.root]) {
    auto hash = AX.hash[v];
    auto it = hc.find(hash);
    if (it == hc.end()) return false;
    it->second.pop_back();
    if (it->second.empty()) hc.erase(it);
  }

  int nby = C.n + 1 - AX.n;
  if (nby % B.n) return false;
  int ny = nby / B.n;
  Y.root = Y.new_node();
  for (auto &e: hc) for (auto &u: e.second) {
    if (C.size[u] < ny) {
      Y.edges[Y.root].push_back(build_from_subtree(C, Y, u));
    }
  }
  if (Y.n != ny) return false;
  BY.root = mul(B, Y, BY, B.root);
  BY.dfs(BY.root);

  for (auto &v: BY.edges[BY.root]) {
    auto hash = BY.hash[v];
    auto it = hc.find(hash);
    if (it == hc.end()) return false;
    it->second.pop_back();
    if (it->second.empty()) hc.erase(it);
  }
  if (reverse) std::swap(X, Y);
  printf("%d %d\n", X.n, Y.n);
  X.print();
  Y.print();
  return true;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int na, nb, nc;
    scanf("%d%d%d", &na, &nb, &nc);
    A.build(na);
    B.build(nb);
    C.build(nc);

    if (solve(A, B, C)) continue;
    if (solve(B, A, C, true)) continue;
    puts("Impossible");
  }
  return 0;
}

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cassert>
#include <vector>
#include <map>

using uint64 = unsigned long long;

const int N = 1e5 + 10;
const int mod = 1e9 + 7;

uint64 seed[N];

struct Tree {
  std::vector<std::vector<int>> edges;
  std::vector<uint64> hash;
  std::vector<int> height, size;
  std::vector<int> parent;
  int n, root, depth, best_u;
  Tree(): edges(), hash(), height(), size(), parent(), n(0), depth(-1) {}
  void init() {
    depth = -1;
    edges.assign(n, {});
    hash.assign(n, 0);
    height.assign(n, 0);
    parent.assign(n, -1);
    size.assign(n, 0);
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
  int new_node() {
    edges.emplace_back();
    hash.emplace_back();
    height.emplace_back();
    parent.emplace_back();
    size.emplace_back();
    return n++;
  }
  void dfs(int u, int d = 0) {
    if (d > depth) depth = d, best_u = u;
    hash[u] = 1; size[u] = 1; height[u] = 1;
    for (auto &v: edges[u]) {
      dfs(v, d + 1);
      height[u] = std::max(height[u], height[v] + 1);
      size[u] += size[v];
    }
    for (auto &v: edges[u]) {
      hash[u] = hash[u] * (seed[height[u]] + hash[v]) % mod;
    }
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
  int delta = C.depth - A.depth;
  if (delta < 0) return false;
  int u = C.best_u;
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
      auto child = build_from_subtree(C, Y, u);
      Y.edges[Y.root].push_back(child);
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
  srand(time(NULL));
  for (int i = 0; i < N; ++i) seed[i] = rand();
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

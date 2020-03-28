#include <cstdio>
#include <cassert>
#include <vector>
#include <tuple>
#include <algorithm>

const int N = 2e5 + 10;
using int64 = long long;

std::vector<int> edges[N];
int A[N], B[N];
int na[N], wa[N];
int nb[N], wb[N];
int n, m;

int64 depth[N], prefix[N];
int st[N], ed[N], top[N], sz;
bool in_cycle[N], mark[N];
int belong[N];
int64 ret[N];

void dfs(int u, int p = -1) {
  top[u] = p == -1 ? u : top[p];
  mark[u] = true;
  st[u] = sz++;
  for (auto &v: edges[u]) if (v != p && !in_cycle[v]) {
    depth[v] = depth[u] + wa[v];
    dfs(v, u);
  }
  ed[u] = sz;
}

struct Fen {
  int u[N], n;
  std::vector<int64> xs;
  void clear() { xs.clear(); }
  void append(int64 x) { xs.push_back(x); }
  void init() {
    std::sort(xs.begin(), xs.end());
    xs.erase(std::unique(xs.begin(), xs.end()), xs.end());
    n = xs.size();
    for (int i = 0; i <= n; ++i) u[i] = 0;
  }
  int id(int64 x) { // i that xs[i] == x
    return std::lower_bound(xs.begin(), xs.end(), x) - xs.begin();
  }
  int uid(int64 x) { // largest i that xs[i] <= x
    return std::upper_bound(xs.begin(), xs.end(), x) - xs.begin() - 1;
  }
  void add(int x, int v) {
    for (; x <= n; x += ~x & x + 1) u[x] += v;
  }
  int get(int x, int r = 0) {
    for (; x >= 0; x -= ~x & x + 1) r += u[x];
    return r;
  }
} f1, f2, tf;

struct Cycle {
  int64 sum;
  std::vector<std::tuple<int64, int, int>> query;
  std::vector<std::pair<int64, int>> subtree;
  std::vector<int64> vs1, vs2;

  void add_tree(int u, int64 d) {
    vs1.push_back((d - prefix[u] + sum) % sum);
    vs2.push_back(prefix[u]);
    subtree.emplace_back(d, u);
  }
  void add_query(int i, int u, int64 t) {
    query.emplace_back(t, u, i);
  }
  void solve() {
    f1.clear(); f2.clear();
    for (auto &e: subtree) {
      f1.append((e.first - prefix[e.second] + sum) % sum);
      f2.append(prefix[e.second]);
    }
    f1.init(); f2.init();
    std::sort(subtree.begin(), subtree.end());
    std::sort(query.begin(), query.end());
    int64 extra = 0;
    for (size_t i = 0, j = 0; i < query.size(); ++i) {
      int64 t = std::get<0>(query[i]);
      int v = std::get<1>(query[i]);
      int idx = std::get<2>(query[i]);
      for (; j < subtree.size() && subtree[j].first <= t; ++j) {
        int64 d = subtree[j].first;
        int u = subtree[j].second;
        extra += (d - prefix[u] + sum) / sum;
        f1.add(f1.id((d - prefix[u] + sum) % sum), 1);
        f2.add(f2.id(prefix[u]), 1);
      }
      ret[idx] += (t - prefix[v]+ sum) / sum * j + j;
      ret[idx] -= extra;
      ret[idx] -= j - f1.get(f1.uid((t - prefix[v] + sum) % sum));
      ret[idx] -= j - f2.get(f2.uid(prefix[v]));
    }
  }
};

namespace tree {
std::vector<std::pair<int, int64>> add[N], sub[N];
std::vector<int64> subtree[N];
int bit[N];

void add_query(int i, int u, int64 t) {
  add[st[u]].emplace_back(i, t + depth[u]);
  sub[ed[u]].emplace_back(i, t + depth[u]);
}
void solve() {
  for (int i = 0; i < m; ++i) {
    tf.append(depth[nb[i]] + wb[i]);
    subtree[st[nb[i]]].push_back(depth[nb[i]] + wb[i]);
  }
  tf.init();
  for (int i = n - 1; i >= 0; --i) {
    for (auto &e: subtree[i]) tf.add(tf.id(e), 1);
    for (auto &e: add[i]) ret[e.first] += tf.get(tf.uid(e.second));
    for (auto &e: sub[i]) ret[e.first] -= tf.get(tf.uid(e.second));
  }
}
}

int main() {
  int l, c, q;
  scanf("%d%d%d%d", &n, &m, &l, &c);
  for (int i = 0; i < n; ++i) scanf("%d", &A[i]);
  for (int i = 0; i < m; ++i) scanf("%d", &B[i]);
  std::reverse(A + (A[0] == 0), A + n);
  std::reverse(B + (B[0] == 0), B + m);
  for (int i = 0; i < n; ++i) A[i] = (l - A[i]) % l;
  for (int i = 0; i < m; ++i) B[i] = (l - B[i]) % l;

  for (int i = 0; i < n; ++i) {
    int x = (A[i] + c) % l;
    int p = std::lower_bound(A, A + n, x) - A;
    if (p == n) na[i] = 0, wa[i] = c + l - x + A[0];
    else na[i] = p, wa[i] = c + A[p] - x;
    edges[na[i]].push_back(i);
  }
  for (int i = 0, j = 0; i < m; ++i) {
    while (j < n && A[j] < B[i]) ++j;
    if (j == n) nb[i] = 0, wb[i] = A[0] + l - B[i];
    else nb[i] = j, wb[i] = A[j] - B[i];
  }

  std::vector<Cycle> cycles;
  for (int i = 0; i < n; ++i) belong[i] = -1;
  for (int i = 0, v; i < n; ++i) if (!mark[i]) {
    for (v = i; !mark[v]; v = na[v]) mark[v] = true;
    cycles.emplace_back();
    auto &cycle = cycles.back();
    cycle.sum = 0;
    for (; mark[v]; v = na[v]) {
      prefix[v] = cycle.sum;
      cycle.sum += wa[v];
      mark[v] = false;
      in_cycle[v] = true;
      belong[v] = cycles.size() - 1;
    }
    for (; !mark[v]; v = na[v]) dfs(v);
  }
  for (int i = 0; i < m; ++i) {
    int u = top[nb[i]];
    cycles[belong[u]].add_tree(u, depth[nb[i]] + wb[i]);
  }

  scanf("%d", &q);
  for (int i = 0, v; i < q; ++i) {
    int64 t;
    scanf("%d%lld", &v, &t);
    --v;
    if (A[0] == 0) v = v > 0 ? n - v : 0;
    else v = n - 1 - v;
    if (belong[v] == -1) {
      tree::add_query(i, v, t);
    } else {
      cycles[belong[v]].add_query(i, v, t);
    }
  }

  tree::solve();
  for (auto &cycle: cycles) {
    cycle.solve();
  }

  for (int i = 0; i < q; ++i) printf("%lld\n", ret[i]);
  return 0;
}

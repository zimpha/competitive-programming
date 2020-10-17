#include <cstdio>
#include <vector>
#include <set>

const int N = 3e5 + 10, M = 3e5 + 10;

int from[M], to[M], is_tree[M], ret[M];
std::vector<int> edges[N];
int depth[N], low[N], high[N];
bool visited[N];

void dfs0(int u) {
  for (auto &e: edges[u]) {
    int v = from[e] + to[e] - u;
    if (visited[v]) continue;
    is_tree[e] = true;
    depth[v] = depth[u] + 1;
    dfs0(v);
  }
}

std::vector<int> bad[N];
void dfs1(int u, int p = -1) {
  low[u] = -1;
  for (auto &e: edges[u]) {
    int v = from[e] + to[e] - u;
    if (is_tree[e]) {
      if (e == p) continue;
      if (low[v] != -1 && (low[u] == -1 || low[v] < low[u])) {
        low[u] = low[v];
      }
      if (low[v] == -1) {
        bad[u].push_back(v);
      }
    } else if (low[u] == -1 || depth[v] < low[u]) {
      low[u] = depth[v];
    }
  }
}

std::set<int> anc[N];
std::vector<int> stk;
void dfs2(int u, int p = -1) {
  stk.push_back(u);
  for (auto &e: edges[u]) if (is_tree[e] && e != p) {
    int v = from[e] + to[e] - u;
    dfs2(v, e);
    anc[v].erase(depth[u]);
    high[v] = anc[v].empty() ? depth[u] : *anc[v].rbegin();
    if (anc[v].size() > anc[u].size()) {
      std::swap(anc[u], anc[v]);
    }
    for (auto &x: anc[v]) anc[u].insert(x);
  }
  if (p != -1) {
    int parent = from[p] + to[p] - u;
    bool found = false;
    if (bad[parent].empty() || (bad[parent].size() == 1 && bad[parent][0] == u)) found = false;
    else found = true;
    for (auto &e: edges[u]) if (is_tree[e] && e != p) {
      int v = from[e] + to[e] - u;
      if (low[v] == -1 || low[v] == depth[parent]) found = true;
    }
    ret[p] = !found;
  }
  for (auto &e: edges[u]) if (!is_tree[e]) {
    int v = from[e] + to[e] - u;
    anc[u].insert(depth[v]);
  }
  stk.pop_back();
  if (!bad[u].empty()) return;
  std::vector<std::pair<int, int>> ae; // ancestor edges
  std::vector<std::pair<int, int>> ce; // child edges
  for (auto &e: edges[u]) {
    int v = from[e] + to[e] - u;
    if (!is_tree[e]) {
      int next = stk[depth[v] + 1];
      if (bad[v].empty() || (bad[v].size() == 1 && bad[v][0] == next)) {
        ae.emplace_back(depth[v], e);
      }
    } else if (e != p) {
      ce.emplace_back(low[v], high[v]);
    }
  }
  std::sort(ae.begin(), ae.end());
  std::sort(ce.begin(), ce.end());
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; ++i) {
    scanf("%d%d", &from[i], &to[i]);
    --from[i], --to[i];
    edges[from[i]].push_back(i);
    edges[to[i]].push_back(i);
  }
  dfs0(0);
  dfs1(0);
  for (int i = 0; i < m; ++i) {
    putchar('0' + ret[i]);
  }
  puts("");
  return 0;
}

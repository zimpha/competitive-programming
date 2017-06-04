#include <cstdio>
#include <set>
#include <map>
#include <utility>
#include <algorithm>

const int N = 200000 + 10, mod = 1e9 + 7;

struct Edge {
  int x, y;
  int opp(int z) {return x + y - z;}
} E[N];

std::map<std::pair<int, int>, int> bridge_id;
std::set<int> G[N];

struct Node {
  int mul, sz, sum;
  void mark(int x) {
    mul = 1ll * mul * x % mod;
  }
  int weight() const {
    return 1ll * mul * sum % mod;
  }
} tag[N];
int fa[N], sz, n;
int a[N];

int dfs_cnt;
void dfs(int u, int f) {
  if (--dfs_cnt == 0) return;
  for (auto &e: G[u]) {
    int v = E[e].opp(u);
    if (v == f) continue;
    dfs(v, u);
    if (!dfs_cnt) return;
  }
}

void split(int u, int f, int id) {
  tag[fa[u]].sum = (tag[fa[u]].sum + mod - a[u]) % mod;
  tag[fa[u]].sz -= 1;
  tag[id].sz += 1;
  tag[id].sum = (tag[id].sum + a[u]) % mod;
  fa[u] = id;
  for (auto &e: G[u]) {
    int v = E[e].opp(u);
    if (v == f) continue;
    split(v, u, id);
  }
}

int solve(int rid, int last) {
  int x = E[rid].x, y = E[rid].y, id = fa[x];
  last = (last - tag[id].weight() + mod) % mod;
  G[x].erase(rid);
  G[y].erase(rid);
  int small;
  for (int i = 1; ; i <<= 1) {
    dfs_cnt = i;
    dfs(x, y);
    int xrem = dfs_cnt;
    dfs_cnt = i;
    dfs(y, x);
    int yrem = dfs_cnt;
    if (!xrem && !yrem) continue;
    small = xrem > yrem ? x : y;
    break;
  }
  int block_size = tag[id].sz;
  tag[sz].mul = tag[id].mul;
  tag[sz].sz = 0;
  tag[sz].sum = 0;
  split(small, x + y - small, sz);
  tag[id].mark(tag[sz].sz + 1);
  tag[sz].mark(tag[id].sz + 1);
  last = (last + tag[id].weight()) % mod;
  last = (last + tag[sz].weight()) % mod;
  ++sz;
  return last;
}

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", a + i);
  }
  sz = 1;
  tag[0].mul = 1;
  tag[0].sz = n;
  for (int i = 0; i < n; ++i) {
    tag[0].sum = (tag[0].sum + a[i]) % mod;
  }
  for (int i = 0; i + 1 < n; ++i) {
    scanf("%d%d", &E[i].x, &E[i].y);
    --E[i].x; --E[i].y;
    if (E[i].x > E[i].y) std::swap(E[i].x, E[i].y);
    bridge_id[std::make_pair(E[i].x, E[i].y)] = i;
    G[E[i].x].insert(i);
    G[E[i].y].insert(i);
  }
  int last = 0;
  for (int i = 1; i < n; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    u += last;
    v += last;
    --u, --v;
    if (u > v) std::swap(u, v);
    int x = bridge_id[std::make_pair(u, v)];
    if (i == 1) last = tag[0].sum;
    last = solve(x, last);
    printf("%d\n", last);
  }
  return 0;
}

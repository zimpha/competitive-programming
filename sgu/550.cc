#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200000 + 10, M = 99990001;

struct Edge {
  int x, y, w;
  int opp(int z) {return x + y - z;}
} E[MAXN];
set<int> G[MAXN];

struct Node {
  int add, mul;
  void mark(int x, int y) {
    mul = 1ll * mul * x % M;
    add = (1ll * add * x + y) % M;
  }
} tag[MAXN];
int fa[MAXN], sz, n;

int dfs_cnt, minv;
void dfs(int u, int f) {
  dfs_cnt--; minv = min(minv, u);
  if (dfs_cnt == 0) return;
  for (auto &e: G[u]) {
    int v = E[e].opp(u); if (v == f) continue;
    dfs(v, u);
    if (!dfs_cnt) return;
  }
}

void split(int u, int f, int id) {
  fa[u] = id;
  for (auto &e: G[u]) {
    int v = E[e].opp(u); if (v == f) continue;
    split(v, u, id);
  }
}

void solve(int rid) {
  int x = E[rid].x, y = E[rid].y, id = fa[x];
  int w = (1ll * E[rid].w * tag[id].mul + tag[id].add) % M;
  printf("%d\n", w); fflush(stdout);
  G[x].erase(rid); G[y].erase(rid);
  int small;
  for (int i = 1; ; i <<= 1) {
    dfs_cnt = i; minv = x;
    dfs(x, y);
    int xrem = dfs_cnt, xmin = minv;
    dfs_cnt = i; minv = y;
    dfs(y, x);
    int yrem = dfs_cnt, ymin = minv;
    if (!xrem && !yrem) continue;
    if (xrem == yrem) small = xmin < ymin ? x : y;
    else small = xrem > yrem ? x : y; break;
  }
  tag[sz].mul = tag[id].mul; tag[sz].add = tag[id].add;
  tag[sz].mark(w, 0); tag[id].mark(1, w);
  split(small, x + y - small, sz++);
}

void run() {
  scanf("%d", &n); sz = 1;
  tag[0].mul = 1; tag[0].add = 0;
  for (int i = 0; i + 1 < n; ++i) {
    scanf("%d%d%d", &E[i].x, &E[i].y, &E[i].w);
    --E[i].x; --E[i].y;
    G[E[i].x].insert(i); G[E[i].y].insert(i);
  }
  for (int i = 1; i < n; ++i) {
    int x; scanf("%d", &x);
    solve(x - 1);
  }
}

int main() {
  run();
  return 0;
}

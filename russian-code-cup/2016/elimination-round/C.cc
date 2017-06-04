#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>

const int N = 200000 + 10, mod = 1e9 + 7;

std::vector<int> edges[N];
int ht[N], valid[N], n;

void dfs1(int u, int p = -1) {
  valid[u] = true;
  ht[u] = 0;
  int cnt = 0;
  for (auto &&v: edges[u]) {
    if (v == p) continue;
    dfs1(v, u);
    ++cnt;
    ht[u] = std::max(ht[u], ht[v] + 1);
    valid[u] &= valid[v];
  }
  valid[u] &= cnt <= 2;
}

int best, ver;
void dfs2(int u, int hp, int p = -1) {
  int cnt = p != -1;
  int cv = p != -1;
  std::multiset<int> ah;
  if (p != -1) ah.insert(hp);
  hp = std::max(hp + 1, ht[u]);
  for (auto &&v: edges[u]) {
    if (v == p) continue;
    ah.insert(ht[v]);
    cv += valid[v];
    cnt += 1;
  }
  if (valid[u] & (cnt <= 2)) {
    if (best == -1 || best > hp + 1 || (best == hp + 1 && u < ver)) {
      best = hp + 1, ver = u;
    }
  }
  for (auto &&v: edges[u]) {
    if (v == p) continue;
    ah.erase(ah.find(ht[v]));
    if (cnt - 1 == cv - valid[v] && cnt - 1 <= 2) {
      int h = ah.size() ? *ah.rbegin() + 1 : 0;
      dfs2(v, h, u);
    }
    ah.insert(ht[v]);
  }
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
      edges[i].clear();
    }
    for (int i = 1; i < n; ++i) {
      int u, v;
      scanf("%d%d", &u, &v);
      edges[u - 1].push_back(v - 1);
      edges[v - 1].push_back(u - 1);
    }
    dfs1(0);
    best = -1;
    dfs2(0, -1);
    int ret = 1;
    for (int i = 0; i < best; ++i) {
      ret = ret * 2 % mod;
    }
    if (best == -1) puts("-1");
    else printf("%d %d\n", ver + 1, (ret + mod - n - 1) % mod);
  }
  return 0;
}

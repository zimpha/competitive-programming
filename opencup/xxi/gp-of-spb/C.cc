#include <cstdio>
#include <cassert>
#include <vector>
#include <cstring>
#include <functional>
#include <algorithm>

using i64 = long long;

const int mod = 998244353;
const int N = 3e5 + 10;

std::vector<int> edges[N];
std::vector<int> tree[N * 2];
i64 dp[N * 2];

class Articulation {
public:
  std::vector<int> keyV, cc[N];      // cc[p]表示结点p在哪些双连通分量中
  int cnt;  // 对于旧版编译器，将上面cc[N]改成vector的形式
  // 传入结点个数n及各结点的出边e[]，返回双连通分量的个数cnt
  int run(int n, const std::vector<int> G[]){
    memset(dfn, use = 0, sizeof(dfn[0]) * n);
    memset(low, cnt = 0, sizeof(low[0]) * n);
    fill_n(cc, n, keyV = std::vector<int>());
    for(int i = 0; i < n; ++i) {
      if(!dfn[i]) dfs(i, 1, G);
    }
    return cnt;
  }
private:
  int dfn[N], low[N], dot[N], use;
  void dfs(int x, int dep, const std::vector<int> G[]){
    int src = 0, out = 1 < dep;
    dot[use++] = x;
    dfn[x] = low[x] = dep;
    for (auto &y: G[x]) {
      if (!dfn[y]){
        dfs(y, dep + 1, G);
        low[x] = std::min(low[x], low[y]);
        if (low[y] >= dfn[x]){
          if (++out == 2) keyV.push_back(x);
          while (dot[--use] != y) cc[dot[use]].push_back(cnt);
          cc[x].push_back(cnt);
          cc[y].push_back(cnt++);
        }
      } else if (dfn[y] != dfn[x] - 1 || src++){
        low[x] = std::min(low[x], dfn[y]);
      }
    }
  }
} tarjan;

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    --u, --v;
    edges[u].push_back(v);
    edges[v].push_back(u);
  }
  m = tarjan.run(n, edges);
  for (int i = 0; i < n; ++i) {
    for (auto &x: tarjan.cc[i]) {
      tree[i].push_back(x + n);
      tree[x + n].push_back(i);
    }
  }

  i64 ret = n + 1;

  std::function<void(int, int)> dfs = [&](int x, int p) {
    dp[x] = 1;
    i64 extra = 0;
    for (auto &y: tree[x]) if (y != p) {
      dfs(y, x);
      dp[x] = dp[x] * (dp[y] + 1) % mod;
      extra += dp[y];
    }
    if (x < n) {
      dp[x] = (dp[x] + mod - 1) % mod;
      ret += dp[x] - extra % mod;
    } else {
      ret += dp[x];
    }
  };

  dfs(0, -1);

  ret %= mod; ret += mod;
  printf("%lld\n", ret % mod);
  return 0;
}

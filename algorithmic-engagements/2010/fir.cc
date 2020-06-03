#include <cstdio>
#include <vector>
#include <algorithm>

using pii = std::pair<int, int>;
const int N = 100000 + 10;

std::vector<int> G[N];
std::vector<pii> level[N];
int q[N], x[N], y[N];
int st[N], ed[N], pos[N];
int seq[N], cnt[N];
int dep[N];
int n, p, sz;

struct BIT {
  std::vector<int> u;
  int n;
  void init(int n) {
    u.resize(n + 2); this->n = n;
    fill(u.begin(), u.end(), 0);
  }
  void modify(int x, int v) {
    for (++ x; x <= n; x += x & -x) u[x] += v;
  }
  int getsum(int x) {
    int ret = 0;
    for (++ x; x; x -= x & -x) ret += u[x];
    return ret;
  }
} Task[N];

void dfs(int u, int d) {
  level[d].emplace_back(sz, u);
  st[u] = sz ++; dep[u] = d;
  for (auto &v: G[u]) dfs(v, d + 1);
  ed[u] = sz;
}

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++ i) {
    char st[100];
    scanf("%s%d%d", st, x + i, y + i);
    q[i] = (st[0] == 'Z');
    if (q[i]) G[y[i]].push_back(x[i]);
  }
  dfs(1, 0);
  for (int i = 0; i < N; ++ i) {
    sort(level[i].begin(), level[i].end());
    for (int j = 0; j < (int)level[i].size(); ++ j) {
      pos[level[i][j].second] = j;
    }
    Task[i].init(level[i].size());
  }
  for (int _ = 0; _ < n; ++ _) {
    int u = x[_], d = y[_];
    if (q[_]) Task[dep[u]].modify(pos[u], 1);
    else {
      d += dep[u] + 1;
      if (d >= n || level[d].empty()) {
        puts("0");
        continue;
      }
      auto &now = level[d];
      int l = lower_bound(now.begin(), now.end(), pii(st[u], -1)) - now.begin();
      int r = lower_bound(now.begin(), now.end(), pii(ed[u], -1)) - now.begin();
      printf("%d\n", Task[d].getsum(r - 1) - Task[d].getsum(l - 1));
    }
  }
  return 0;
}

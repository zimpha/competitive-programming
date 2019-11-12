#include <cstdio>
#include <vector>
#include <algorithm>

const int N = 2000 + 10;

std::vector<std::pair<int, int>> edges[N];
int dp[N][N][2];

int main() {
  int n, m, k;
  scanf("%d%d%d", &n, &m, &k);
  int mi = m, mx = 0;
  std::vector<std::pair<int, int>> s;
  for (int i = 0; i < n; ++i) {
    int l, r;
    scanf("%d%d", &l, &r);
    mi = std::min(mi, l);
    mx = std::max(mx, r);
    s.emplace_back(l, -(i + 1));
    s.emplace_back(r, +(i + 1));
  }
  int ret = m - mx + mi;
  std::sort(s.begin(), s.end());
  std::vector<int> val(n), deg(n);
  for (size_t i = 1; i < s.size(); ++i) {
    int l = s[i - 1].first, sl = s[i - 1].second;
    int r = s[i].first, sr = s[i].second;
    int a = std::abs(sl) - 1;
    int b = std::abs(sr) - 1;
    if (sl > 0 && sr > 0) val[b] += r - l;
    if (sl > 0 && sr < 0) ret += r - l;
    if (sl < 0 && sr > 0) {
      if (a == b) val[a] += r - l;
      else {
        deg[a]++, deg[b]++;
        edges[a].emplace_back(b, r - l);
        edges[b].emplace_back(a, r - l);
      }
    }
    if (sl < 0 && sr < 0) val[a] += r - l;
  }
  std::vector<int> nodes;
  std::vector<int> cost;
  std::vector<bool> mark(n);
  for (int i = 0; i < n; ++i) if (!mark[i] && deg[i] <= 1) {
    cost.push_back(0);
    nodes.push_back(i);
    mark[i] = 1;
    for (int u = i; deg[u]; ) {
      deg[u] = 0;
      mark[u] = 1;
      for (auto &e: edges[u]) if (deg[e.first]) {
        u = e.first;
        nodes.push_back(u);
        cost.push_back(e.second);
        break;
      }
    }
  }
  dp[0][0][0] = 0;
  dp[0][1][1] = val[nodes[0]];
  for (int i = 0; i + 1 < n; ++i) {
    for (int j = 0; j <= i + 1 && j <= k; ++j) {
      dp[i + 1][j][0] = std::max(dp[i][j][0], dp[i][j][1]);
      dp[i + 1][j + 1][1] = std::max(dp[i][j][0], dp[i][j][1] + (j ? cost[i + 1] : 0)) + val[nodes[i + 1]];
    }
  }
  printf("%d\n", ret + std::max(dp[n - 1][k][0], dp[n - 1][k][1]));
  return 0;
}

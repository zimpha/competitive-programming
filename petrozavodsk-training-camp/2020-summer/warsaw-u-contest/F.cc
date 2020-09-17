#include <cstdio>
#include <vector>
#include <queue>

const int N = 3e5 + 10;

std::vector<int> edges[N];
std::priority_queue<int> dp[N];

void dfs(int u) {
  for (auto &v: edges[u]) {
    dfs(v);
    if (dp[u].size() < dp[v].size()) std::swap(dp[u], dp[v]);
    while (!dp[v].empty()) {
      dp[u].push(dp[v].top());
      dp[v].pop();
    }
  }
  int s = 0;
  for (int it = 0; it < 2 && dp[u].size(); ++it) {
    s += dp[u].top();
    dp[u].pop();
  }
  dp[u].push(s + 1);
}

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1, p; i < n; ++i) {
    scanf("%d", &p);
    edges[p - 1].push_back(i);
  }
  dfs(0);
  printf("%d\n", dp[0].top());
  return 0;
}

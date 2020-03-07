#include <cstdio>
#include <cstring>
#include <vector>

const int N = 5000 + 10;
const int mod = 1e9 + 7;

int dp[N][N];
int a[N], col[N];
int c0, c1, n, m;

bool dfs(int u, int c) {
  if (col[u] != -1) return col[u] == c;
  if (c == 0) ++c0;
  else ++c1;
  col[u] = c;
  for (int v = 0; v < n; ++v) {
    if ((u < v && a[u] > a[v]) || (u > v && a[v] > a[u])) {
      if (!dfs(v, c ^ 1)) return false;
    }
  }
  return true;
}

void add(int &x, int y) {
  if ((x += y) >= mod) x -= mod;
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
  memset(col, -1, sizeof(col));
  bool valid = true;
  std::vector<std::pair<int, int>> s;
  for (int i = 0; i < n && valid; ++i) if (col[i] == -1) {
    c0 = c1 = 0;
    if (!dfs(i, 0)) valid = false;
    s.emplace_back(c0, c1);
  }
  if (!valid) {
    puts("0");
    return 0;
  }
  dp[0][0] = 1;
  int sum = 0;
  for (auto &e: s) {
    int u = e.first, v = e.second;
    for (int i = 0; i <= sum && i <= m; ++i) {
      if (!dp[i][sum - i]) continue;
      if (i + u <= m && sum - i + v <= m) add(dp[i + u][sum - i + v], dp[i][sum - i]);
      if (i + v <= m && sum - i + u <= m) add(dp[i + v][sum - i + u], dp[i][sum - i]);
    }
    sum += u + v;
  }
  int ret = 0;
  for (int i = n - m; i <= m; ++i) {
    add(ret, dp[i][n - i]);
  }
  printf("%d\n", ret);
  return 0;
}

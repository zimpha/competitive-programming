#include <bits/stdc++.h>
using namespace std;

using LL = long long;

int max_depth, max_len;

LL dfs(LL cur, bool vis[], int d, LL val) {
  if (d == max_depth) return val >> max_len;
  if (vis[cur]) return 0;
  vis[cur] = true;
  LL ret = dfs(cur << 1 & (max_depth - 1), vis, d + 1, val << 1);
  ret += dfs((cur << 1 | 1) & (max_depth - 1), vis, d + 1, val << 1 | 1);
  vis[cur] = false;
  if (d == max_depth - 1) return ret >> 1;
  else return ret;
}

LL run(int n) {
  int m = 1 << n;
  bool vis[m];
  for (int i = 0; i < m; ++i) vis[i] = 0;
  max_depth = m, max_len = n;
  return dfs(0, vis, 0, 0);
}

int main() {
  std::cout << run(3) << std::endl;
  std::cout << run(5) << std::endl;
  return 0;
}


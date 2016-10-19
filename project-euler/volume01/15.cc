#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

LL sol(int n, int m) {
  vector<vector<LL> > g;
  g.assign(n + 1, vector<LL>(m + 1, 0));
  for (int i = 0; i <= n; ++ i) {
    for (int j = 0; j <= m; ++ j) {
      if (i == 0 || j == 0) g[i][j] = 1;
      else g[i][j] = g[i - 1][j] + g[i][j - 1];
    }
  }
  return g[n][m];
}

int main() {
  cout << sol(20, 20) << endl;
  return 0;
}

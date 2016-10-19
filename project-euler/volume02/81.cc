#include <bits/stdc++.h>
using namespace std;

void upd(int &x, int y) {
  if (x == -1 || x > y) x = y;
}

int sol(int n, int m) {
  vector<vector<int> > g;
  g.assign(n, vector<int>());
  for (int i = 0; i < n; ++ i) {
    for (int j = 0; j < m; ++ j) {
      int x; cin >> x;
      g[i].push_back(-1);
      if (i) upd(g[i][j], g[i - 1][j] + x);
      if (j) upd(g[i][j], g[i][j - 1] + x);
      if (!i && !j) g[i][j] = x;
    }
  }
  return g[n - 1][m - 1];
}

int main() {
  cout << sol(80, 80) << endl;
  return 0;
}

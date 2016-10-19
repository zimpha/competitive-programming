#include <bits/stdc++.h>
using namespace std;

int sol(int n, int m) {
  vector<vector<int> > g;
  g.assign(n, vector<int>(m));
  for (int i = 0; i < n; ++ i) {
    for (int j = 0; j < m; ++ j) {
      cin >> g[i][j];
    }
  }
  int ret(0);
  for (int x = 0; x < n; ++ x) {
    for (int y = 0; y < m; ++ y) {
      const int dx[] = {0, 1, 1, -1};
      const int dy[] = {1, 0, 1, 1};
      for (int k = 0; k < 4; ++ k) {
        int tmp(1);
        for (int i = 0; i < 4; ++ i) {
          int xx = x + i * dx[k], yy = y + i * dy[k];
          if (xx < 0 || xx >= n || yy < 0 || yy >= m) {
            tmp = 0; break;
          }
          tmp *= g[x + i * dx[k]][y + i * dy[k]];
        }
        ret = max(ret, tmp);
      }
    }
  }
  return ret;
}

int main() {
  cout << sol(20, 20) << endl;
  return 0;
}

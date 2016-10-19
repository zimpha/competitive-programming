#include <bits/stdc++.h>
using namespace std;

int sol(int n) {
  vector<vector<int> > g;
  g.assign(n, vector<int>());
  for (int i = 0; i < n; ++ i) {
    for (int j = 0; j <= i; ++ j) {
      int x; scanf("%d", &x);
      g[i].push_back(x);
      if (i) {
        if (j) g[i][j] = max(g[i - 1][j], g[i - 1][j - 1]) + x;
        else g[i][j] = x + g[i - 1][j];
      }
    }
  }
  return *max_element(g[n - 1].begin(), g[n - 1].end());
}

int main() {
  cout << sol(100) << endl;
  return 0;
}

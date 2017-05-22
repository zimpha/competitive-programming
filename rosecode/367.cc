#include <bits/stdc++.h>

int f[1000][1000], g[1000][1000];

int main() {
  std::string s, t;
  std::cin >> s >> t;
  int n = s.size(), m = t.size();
  for (int i = 0; i <= n; ++i) {
    for (int j = 0; j <= m; ++j) {
      f[i][j] = -1e9;
      g[i][j] = 0;
    }
  }
  std::cout << n << ' ' << m << std::endl;
  f[0][0] = 0;
  for (int i = 0; i <= n; ++i) {
    for (int j = 0; j <= m; ++j) {
      if (!i && !j) continue;
      if (i && j) {
        if (s[i] == t[j] && f[i - 1][j - 1] + 2 > f[i][j]) {
          f[i][j] = f[i - 1][j - 1] + 2;
          g[i][j] = g[i - 1][j - 1] + 1;
        }
        if (s[i] != t[j] && f[i - 1][j - 1] - 1 > f[i][j]) {
          f[i][j] = f[i - 1][j - 1] - 1;
          g[i][j] = g[i - 1][j - 1];
        }
      }
      if (i && f[i - 1][j] - 2 > f[i][j]) {
        f[i][j] = f[i - 1][j] - 2;
        g[i][j] = g[i - 1][j];
      }
      if (j && f[i][j - 1] - 2 > f[i][j]) {
        f[i][j] = f[i][j - 1] - 2;
        g[i][j] = g[i][j - 1];
      }
    }
  }
  std::cout << f[n][m] << ' ' << g[n][m] << std::endl;
  return 0;
}

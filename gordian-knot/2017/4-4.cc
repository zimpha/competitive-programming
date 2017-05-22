#include <bits/stdc++.h>

int g[20][20];

int main() {
  int n, m;
  scanf("%d", &n);
  m = n * (n - 1) / 2;
  int mx = 0;
  for (int msk = 0; msk < (1 << m); ++msk) {
    memset(g, 0, sizeof(g));
    int c = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < i; ++j) {
        if (msk >> c & 1) g[i][j] = 1;
        else g[j][i] = 1;
        ++c;
      }
    }
    int s = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        for (int k = 0; k < n; ++k) {
          s += g[i][j] && g[j][k] && g[k][i];
        }
      }
    }
    mx = std::max(mx, s);
  }
  std::cout << mx / 3 << std::endl;
  return 0;
}

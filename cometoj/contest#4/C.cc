#include <cstdio>
#include <vector>

const int N = 1000 + 10;

char s[N][N];
int g[N][N];

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; ++i) {
      scanf("%s", s[i] + 1);
    }
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= m; ++j) {
        g[i][j] = g[i - 1][j] + g[i][j - 1] - g[i - 1][j - 1] + (s[i][j] == '0');
      }
    }
    if (g[n][m] == 0) {
      for (int i = 1; i <= k; ++i) {
        printf("%d%c", i, " \n"[i == k]);
      }
      continue;
    }
    std::vector<int> ret;
    for (int a = 0; a <= k && a <= n - 1; ++a) {
      int b = k - a;
      if (b < 0 || b > m - 1) continue;
      if (g[n][m] % ((a + 1) * (b + 1))) continue;
      std::vector<int> xs, ys;
      int col_sum = g[n][m] / (b + 1);
      int row_sum = g[n][m] / (a + 1);
      int avg = g[n][m] / ((a + 1) * (b + 1));
      for (int i = 0, j = 0; i <= m; ++i) {
        if (g[n][i] % col_sum == 0 && g[n][i] / col_sum == j) {
          ys.push_back(i);
          ++j;
        }
      }
      if (ys.size() != b + 2) continue;
      ys.pop_back(); ys.push_back(m);
      for (int i = 0, j = 0; i <= n; ++i) {
        if (g[i][m] % row_sum == 0 && g[i][m] / row_sum == j) {
          xs.push_back(i);
          ++j;
        }
      }
      if (xs.size() != a + 2) continue;
      xs.pop_back(); xs.push_back(n);
      bool valid = true;
      for (size_t i = 1; i < xs.size() && valid; ++i) {
        for (size_t j = 1; j < ys.size() && valid; ++j) {
          int sum = g[xs[i]][ys[j]] - g[xs[i]][ys[j - 1]] - g[xs[i - 1]][ys[j]] + g[xs[i - 1]][ys[j - 1]];
          valid &= (sum == avg);
        }
      }
      if (valid) {
        std::vector<int> tmp;
        for (int i = 1; i <= a; ++i) tmp.push_back(xs[i]);
        for (int i = 1; i <= b; ++i) tmp.push_back(ys[i] + n - 1);
        if (ret.empty() || ret > tmp) ret = tmp;
      }
    }
    if (ret.empty()) puts("Impossible");
    else {
      for (int i = 0; i < k; ++i) {
        printf("%d%c", ret[i], " \n"[i == k - 1]);
      }
    }
  }
  return 0;
}

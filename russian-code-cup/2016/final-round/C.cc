#include <cstdio>
#include <algorithm>

const int N = 100000 + 10;

int g[330][N];
int n, m, k;

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    scanf("%d%d%d", &n, &m, &k);
    bool flip = false;
    if (n > m) std::swap(n, m), flip = true;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        g[i][j] = 0;
      }
    }
    if (n <= 4 && m <= 4) {
      bool find = false;
      for (int mask = 1; mask < (1 << (n * m)) && !find; ++mask) {
        for (int i = 0; i < n; ++i) {
          for (int j = 0; j < m; ++j) {
            g[i][j] = mask >> (i * m + j) & 1;
          }
        }
        int cnt = 0;
        for (int i = 0; i < n - 1; ++i) {
          for (int j = 0; j < m - 1; ++j) {
            int t = g[i][j] + g[i + 1][j] + g[i][j + 1] + g[i + 1][j + 1];
            if (t == 3) ++cnt;
            else if (t == 4) cnt += 4;
          }
        }
        if (cnt == k) find = true;
      }
      if (!find) {
        puts("-1\n");
        continue;
      }
    } else if (k > (n - 1) * (m - 1) * 4) {
      puts("-1\n");
      continue;
    } else if (k == (n - 1) * (m - 1) * 4) {
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
          g[i][j] = 1;
        }
      }
    } else if (k == (n - 1) * (m - 1) * 4 - 8) {
      if (n != 3) {
        puts("-1\n");
        continue;
      }
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
          g[i][j] = j > 0;
        }
      }
    } else if (!k) {
      g[0][0] = 1;
    } else {
      --k;
      for (int i = 0; i < m; ++i) g[0][i] = 1;
      int x = 0, y = m - 1;
      for (int i = 1; i < n && k >= 4; ++i) {
        for (int j = 1; j < m && k >= 4; ++j) {
          x = i, y = j;
          g[i][j] = 1;
          k -= 4;
        }
      }
      if (y == m - 1) ++x, y = 0;
      for (int i = 0; i <= x; ++i) g[i][0] = 1;
      if (k == 1) {
        if (x != n - 1) {
          if (y >= 1) g[x + 1][0] = 1;
          else g[x][m - 1] = 1;
        } else if (y < m - 2) {
          g[n - 1][m - 1] = 1;
        } else {
          puts("-1\n");
          continue;
        }
      } else if (k == 2) {
        if (x != n - 1) {
          if (y >= 2) g[x + 1][1] = 1;
          else g[x][m - 2] = 1;
        } else if (y < m - 3) {
          g[x][m - 2] = 1;
        } else {
          puts("-1\n");
          continue;
        }
      } else if (k == 3) {
        if (x != n - 1) {
          if (y >= 3) g[x + 1][0] = g[x + 1][y - 1] = 1;
          else if (y == 2) g[x + 1][1] = g[x][m - 1] = 1;
          else if (y == 1) g[x + 1][0] = g[x][m - 2] = 1;
          else g[x][m - 3] = g[x][m - 1] = 1;
        } else if (y < m - 4) {
          g[x][m - 3] = g[x][m - 1] = 1;
        } else {
          puts("-1\n");
          continue;
        }
      }
    }
    if (flip) {
      for (int j = 0; j < m; ++j) {
        for (int i = 0; i < n; ++i) {
          putchar(g[i][j] ? '*' : '.');
        }
        puts("");
      }
    } else {
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
          putchar(g[i][j] ? '*' : '.');
        }
        puts("");
      }
    }
    puts("");
  }
  return 0;
}

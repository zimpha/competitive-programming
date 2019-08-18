#include <cstdio>
#include <cstring>

const int N = 1000 + 10;

int f[2][N][26];
char s[N];

int main() {
  int n, m;
  scanf("%d%d%s", &n, &m, s);
  memset(f, -1, sizeof(f));
  for (int i = 0; i < 26; ++i) {
    f[0][i != s[0] - 'A'][i] = 1;
  }

  auto update = [&](int &x, int y) {
    if (x == -1 || x > y) x = y;
  };

  for (int i = 1; i < n; ++i) {
    int u = i & 1, v = u ^ 1;
    memset(f[u], -1, sizeof(f[u]));
    for (int j = 0; j <= m; ++j) {
      for (int o = 0; o < 26; ++o) {
        if (f[v][j][o] == -1) continue;
        if (o == s[i] - 'A') {
          update(f[u][j][o], f[v][j][o]);
        } else {
          if (j + 1 <= m) {
            update(f[u][j + 1][o], f[v][j][o]);
          }
          update(f[u][j][s[i] - 'A'], f[v][j][o] + 1);
        }
      }
    }
  }
  int ret = -1;
  for (int i = 0; i <= m; ++i) {
    for (int o = 0; o < 26; ++o) {
      if (f[(n & 1) ^ 1][i][o] != -1) {
        update(ret, f[(n & 1) ^ 1][i][o]);
      }
    }
  }
  printf("%d\n", ret);
  return 0;
}

#include <cstdio>
#include <cstring>
#include <vector>

const int N = 200 + 10;
char s[N][N];
int ps[N][N];
bool mark[N][N];

int ss1(int x1, int y1) {
  if (x1 < 0 || y1 < 0) return 0;
  else return ps[x1][y1];
}

int ss2(int x1, int y1, int x2, int y2) {
  return ps[x2][y2] - ps[x2][y1 - 1] - ps[x1 - 1][y2] + ps[x1 - 1][y1 - 1];
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, m, h, v;
    scanf("%d%d%d%d", &n, &m, &h, &v);
    int sum = 0;
    for (int i = 0; i < n; ++i) {
      scanf("%s", s[i]);
      for (int j = 0; j < m; ++j) {
        sum += s[i][j] == '@';
        ps[i][j] = s[i][j] == '@';
        if (i) ps[i][j] += ps[i - 1][j];
        if (j) ps[i][j] += ps[i][j - 1];
        if (i && j) ps[i][j] -= ps[i - 1][j - 1];
      }
    }
    memset(mark, 0, sizeof(mark));
    int total = (h + 1) * (v + 1);
    if (sum % total != 0) {
      printf("Case #%d: IMPOSSIBLE\n", cas);
      continue;
    }
    if (sum == 0) {
      printf("Case #%d: POSSIBLE\n", cas);
      continue;
    }
    int avg = sum / total;
    sum = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        for (int a = 1; a <= h; ++a) {
          for (int b = 1; b <= v; ++b) {
            if (ss2(0, 0, i, j) == a * b * avg && 
                ss2(i + 1, 0, n - 1, j) == avg * (h + 1 - a) * b &&
                ss2(0, j + 1, i, m - 1) == avg * a * (v + 1 - b) &&
                ss2(i + 1, j + 1, n - 1, m - 1) == avg * (h + 1 - a) * (v + 1 - b)) {
              mark[a][b] = 1;
            }
          }
        }
      }
    }
    bool valid = 1;
    for (int i = 1; i <= h; ++i) {
      for (int j = 1; j <= v; ++j) {
        valid &= mark[i][j];
      }
    }
    if (valid) printf("Case #%d: POSSIBLE\n", cas);
    else printf("Case #%d: IMPOSSIBLE\n", cas);
  }
  return 0;
}

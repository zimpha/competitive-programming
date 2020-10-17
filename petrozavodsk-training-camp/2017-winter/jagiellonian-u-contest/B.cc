#include <cstdio>
#include <cstring>

const int N = 1000000 + 10, M = 1000 + 10;

char s[N], t[N];
int next[N][26];
int dp[M][M];

void update(int &x, int y) {
  if (x == -1 || y < x) x = y;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    scanf("%s%s", s, t);
    int n = strlen(s);
    int m = strlen(t);
    for (int i = 0; i < 26; ++i) next[n][i] = -1;
    for (int i = n - 1; i >= 0; --i) {
      for (int j = 0; j < 26; ++j) {
        next[i][j] = next[i + 1][j];
      }
      next[i][s[i] - 'a'] = i;
    }
    for (int i = 0; i <= m; ++i) {
      for (int j = 0; j <= m; ++j) {
        dp[i][j] = -1;
      }
    }
    dp[0][0] = 0;
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j <= m; ++j) {
        if (dp[i][j] == -1) continue;
        update(dp[i + 1][j], dp[i][j]);
        int v = next[dp[i][j]][t[i] - 'a'];
        if (v != -1) {
          update(dp[i + 1][j + 1], v + 1);
        }
      }
    }
    int ret = 0;
    for (int i = 0; i <= m; ++i) {
      if (dp[m][i] != -1) ret = i;
    }
    printf("%d\n", ret);
  }
  return 0;
}

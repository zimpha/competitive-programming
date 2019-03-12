#include <cstdio>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <algorithm>

const int N = 200 + 10;

int dp[N][N], from[N][N];
char s[N];
char pat[N][N];

void add(int &x, int y) {
  x += y;
  if (x > 1000000) x = 1000000;
}

int main() {
  scanf("%s", s);
  int n, m;
  m = strlen(s);
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) scanf("%s", pat[i]);
  memset(dp, 0, sizeof(dp));
  dp[0][0] = 1;
  for (int i = 0; i < n; ++i) {
    int l = strlen(pat[i]);
    for (int j = 0; j <= m; ++j) if (dp[i][j]) {
      add(dp[i + 1][j], dp[i][j]);
      from[i + 1][j] = -1;
    }
    for (int j = 0; j + l <= m; ++j) if (dp[i][j]) {
      bool valid = true;
      for (int k = 0; k < l && valid; ++k) valid &= s[j + k] == pat[i][k];
      if (valid) {
        add(dp[i + 1][j + l], dp[i][j]);
        from[i + 1][j + l] = i;
      }
    }
  }
  if (dp[n][m] == 0) {
    puts("NIE");
    return 0;
  }
  printf("%d\n", dp[n][m]);
  std::vector<int> result;
  for (int x = n, y = m; x && y; ) {
    if (from[x][y] == -1) --x;
    else {
      int l = strlen(pat[from[x][y]]);
      result.push_back(from[x][y] + 1);
      --x;
      y -= l;
    }
  }
  std::reverse(result.begin(), result.end());
  for (auto &&x: result) printf("%d\n", x);
  return 0;
}

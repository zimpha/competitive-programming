#include <cstdio>
#include <cstring>


const int N = 310;

char s[N][N];
int cost[N][N];
int best[N][N];
int dp[N][N];

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) scanf("%s", s[i]);
  memset(best, -1, sizeof(best));
  best[0][n] = 0;
  for (int i = 0; i + 1 < m; ++i) {
  }
  return 0;
}

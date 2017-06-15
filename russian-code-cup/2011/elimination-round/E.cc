#include <cstdio>
#include <cstring>
#include <algorithm>

const int N = 20, M = 500 + 10;

char s[N];
char dp[N][M][M][M / 10];
int n, m;

int solve(int at, int rest, int prev, int carry) {
  if (at == n) return rest == 0 && carry == 0;
  if (dp[at][rest][prev][carry] != -1) return dp[at][rest][prev][carry];
  int ret = 0;
  int o = s[at] - '0';
  for (int k = 0; k <= rest && k <= prev; ++k) if ((k + carry) % 10 == o) {
    ret |= solve(at + 1, rest - k, k, (k + carry) / 10);
  }
  return dp[at][rest][prev][carry] = ret;
}

int main() {
  scanf("%s%d", s, &m);
  n = strlen(s);
  std::reverse(s, s + n);
  memset(dp, -1, sizeof(dp));
  bool find = false;
  for (int i = 1; i <= m; ++i) {
    if (solve(0, m, i, 0)) {
      printf("%d\n", i);
      find = true;
      break;
    }
  }
  if (!find) puts("Impossible");
  return 0;
}

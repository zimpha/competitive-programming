#include <bits/stdc++.h>

const int N = 500 + 10, M = 500 * 500 * 2 + 10;
char s[N];
int a[N], b[N];
int f[M], g[M], h[M];
int n;

void solve(char c, int* dp) {
  memset(dp, 0, sizeof(*dp) * M);
  int total = 0;
  for (int i = 0; i < n; ++i) {
    if (s[i] == c) {
      //total += a[i] + b[i];
      for (int j = M - 1; j >= a[i] + b[i]; --j) {
        dp[j] = std::max(dp[j], dp[j - a[i] - b[i]] + b[i]);
      }
    }
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    char buf[10];
    scanf("%s%d%d", buf, a + i, b + i);
    s[i] = buf[0];
  }
  solve('L', f);
  solve('D', g);
  solve('W', h);
  int ret = 0;
  for (int i = 0; i < M; ++i) {
    ret = std::max(ret, f[i] + g[i] + h[i] - i);
  }
  printf("%d\n", ret);
  return 0;
}

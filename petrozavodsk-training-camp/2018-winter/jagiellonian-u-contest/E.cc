#include <cstdio>
#include <cstring>
#include <algorithm>

const int K = 15, N = 1 << K, M = 1594323 + 10;

char s[K];
int pw[K], dp[M];
int n, k;

void upd(int &x, int y) {
  if (x == -1 || x > y) x = y;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    scanf("%d%d", &n, &k);
    pw[0] = 1;
    for (int i = 1; i <= k; ++i) pw[i] = pw[i - 1] * 3;
    for (int i = 0; i < pw[k]; ++i) {
      dp[i] = -1;
    }
    for (int i = 0; i < n; ++i) {
      scanf("%s", s);
      int x = 0, w = 0;
      for (int j = 0; j < k; ++j) {
        x = x * 2 + s[j] - '0';
      }
      for (int j = 0; j < k; ++j) {
        w += (1 + (x >> j & 1)) * pw[j];
      }
      dp[w] = 0;
    }
    for (int mask = pw[k] - 1; mask >= 0; --mask) {
      int &ret = dp[mask];
      for (int i = 0; i < k; ++i) {
        int o = mask / pw[i] % 3;
        if (o != 0) continue;
        int u = mask + pw[i], v = u + pw[i];
        if (dp[u] == -1 && dp[v] == -1) continue;
        if (dp[u] == -1 && dp[v] != -1) upd(ret, dp[v]);
        if (dp[u] != -1 && dp[v] == -1) upd(ret, dp[u]);
        if (dp[u] != -1 && dp[v] != -1) upd(ret, std::max(dp[u], dp[v]) + 1);
      }
    }
    printf("%d\n", dp[0]);
  }
  return 0;
}

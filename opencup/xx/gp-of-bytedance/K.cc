#include <bits/stdc++.h>

const int N = 1000000;
const int MOD = 1e9 + 7;

int n, ones, diag[N], head[N], to[N], next[N], weight[N], dp[N][2][2], up[N],
    down[N];

void add_edge(int i, int u, int v, int w) {
  to[i] = v;
  weight[i] = w;
  next[i] = head[u];
  head[u] = i;
}

void dfs(int piter, int u) {
  // dp = (is u unmatched) * (is J chosen)
  int sum[2][2]; // is u matched * is J chosen in the subtree
  memset(sum, 0, sizeof(sum));
  sum[0][0] = 1;
  int sumud[2][2];
  memset(sumud, 0, sizeof(sumud));
  sumud[0][0] = 1;
  for (int iter = head[u]; ~iter; iter = next[iter]) {
    int v = to[iter];
    if ((iter ^ piter) != 1) {
      dfs(iter, v);
      for (int x = 2; x--;) {
        for (int y = 2; y--;) {
          uint64_t tmp = 1ULL * sum[x][y] * dp[v][0][0];
          int m = (MOD - 1ULL) * weight[iter] % MOD * weight[iter ^ 1] % MOD;
          if (x) {
            tmp += 1ULL * sum[x - 1][y] * m % MOD * dp[v][1][0];
          }
          if (x && y) {
            tmp += 1ULL * sum[x - 1][y - 1] * m % MOD * dp[v][1][1];
          }
          if (y) {
            tmp += 1ULL * sum[x][y - 1] * dp[v][0][1];
          }
          sum[x][y] = tmp % MOD;
        }
      }
      for (int x = 2; x--;) {
        for (int y = 2; y--;) {
          uint64_t tmp = 1ULL * sumud[x][y] * dp[v][0][0];
          if (x) {
            tmp += 1ULL * sumud[x - 1][y] * up[v];
          }
          if (y) {
            tmp += 1ULL * sumud[x][y - 1] * down[v];
          }
          sumud[x][y] = tmp % MOD;
        }
      }
    }
  }
  dp[u][1][0] = sum[0][0];
  dp[u][0][0] = (sum[1][0] + 1LL * diag[u] * sum[0][0]) % MOD;
  dp[u][1][1] = sum[0][1];
  dp[u][0][1] =
      (sum[1][1] + 1LL * diag[u] * sum[0][1] +
       (1LL * sum[0][0] + sumud[0][1] + sumud[1][0] + sumud[1][1]) * ones) %
      MOD;
  if (~piter) {
    up[u] = 1LL * (sumud[0][0] + sumud[1][0]) * weight[piter ^ 1] % MOD;
    down[u] = 1LL * (sumud[0][0] + sumud[0][1]) * weight[piter] % MOD;
  }
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &ones);
    for (int i = 0; i < n; ++i) {
      scanf("%d", diag + i);
      diag[i] = (MOD - 1LL) * (diag[i] + MOD - ones) % MOD;
    }
    memset(head, -1, sizeof(*head) * n);
    for (int i = 1, p, a, b; i < n; ++i) {
      scanf("%d%d%d", &p, &a, &b);
      p--;
      add_edge(i - 1 << 1, p, i, (a + MOD - ones) % MOD);
      add_edge((i << 1) - 1, i, p, (b + MOD - ones) % MOD);
    }
    ones = (MOD - 1LL) * ones % MOD;
    dfs(-1, 0);
    int result = (dp[0][0][0] + dp[0][0][1]) % MOD;
    if (n & 1) {
      result = (MOD - 1LL) * result % MOD;
    }
    printf("%d\n", result);
  }
}

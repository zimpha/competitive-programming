#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

using int64 = long long;

const int N = 2000 + 10;
const int mod = 998244353;

std::vector<int> edges[N];

// subtree i, j path, has path out
int64 dp[N][N][2];
int size[N];
int n;

int64 pow_mod(int64 a, int64 n) {
  int64 r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % mod;
    a = a * a % mod;
  }
  return r;
}

void dfs(int u, int p = -1) {
  size[u] = 1;
  for (auto &&v: edges[u]) {
    if (v == p) continue;
    dfs(v, u);
    size[u] += size[v];
  }
  if (size[u] == 1) {
    dp[u][0][0] = 1;
    dp[u][1][0] = 1;
    dp[u][1][1] = 1;
  } else {
    // f: root not covered
    // g: root covered, no out
    // h: root covered, has out
    static int64 f[2][N], g[2][N], h[2][N];
    memset(f, 0, sizeof(f));
    memset(g, 0, sizeof(g));
    memset(h, 0, sizeof(h));
    f[0][0] = 1;
    int sum = 0;
    int t = 0;
    for (auto &&v: edges[u]) {
      if (v == p) continue;
      for (int i = 0; i <= sum; ++i) {
        for (int j = 0; j <= size[v]; ++j) {
          f[t ^ 1][i + j] = f[t][i] * dp[v][j][0] % mod;
          g[t ^ 1][i + j] = (g[t][i] * dp[v][j][0] + dp[v][j][1] * f[t][i] + dp[v][j][1] * h[t][i]) % mod;
          h[t ^ 1][i + j] = (h[t][i] * dp[v][j][0] + f[t][i] * dp[v][j][1]) % mod;
        }
      }
      t ^= 1;
      sum += size[v];
    }
    for (int i = 0; i <= size[u]; ++i) {
      dp[u][i][0] = f[t][i] + g[t][i];
      if (i) dp[u][i][0] += f[t][i - 1];
      dp[u][i][1] = h[t][i];
      if (i) dp[u][i][1] += f[t][i - 1];
    }
    for (int i = 0; i <= size[u]; ++i) {
      dp[u][i][0] %= mod;
      dp[u][i][1] %= mod;
    }
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i < n; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    edges[u - 1].emplace_back(v - 1);
    edges[v - 1].emplace_back(u - 1);
  }
  dfs(0);
  int64 inv = pow_mod(n * (n + 1) / 2, mod - 2);
  int64 p = 1, fac = 1;
  int64 ret = 0;
  for (int i = 1; i <= n; ++i) {
    fac = fac * i % mod;
    p = p * inv % mod;
//    printf("%lld\n", dp[0][i][0] * fac);
    ret += dp[0][i][0] * p % mod * fac % mod;
  }
  printf("%lld\n", ret % mod);
  return 0;
}

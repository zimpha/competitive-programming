#include <cstdio>
#include <vector>
#include <algorithm>

using int64 = long long;

const int N = 1e6 + 10;
const int64 inf = 4e18 + 10;

int64 dp[N * 4], sum[N * 4][2];
char a[N], b[N];
std::vector<int> stk[2];

int idx(char c) {
  return '0' <= c && c <= '9' ? c - '0' : c - 'A' + 10;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    int64 t0, t1, ts;
    scanf("%d%lld%lld%lld", &n, &t0, &t1, &ts);
    scanf("%s%s", a, b);
    stk[0] = stk[1] = {};
    dp[0] = 0; sum[0][0] = sum[0][1] = 0;
    for (int i = 0, p = 1; i < n; ++i) {
      a[i] = idx(a[i]); b[i] = idx(b[i]);
      for (int j = 3; j >= 0; --j, p++) {
        int x = a[i] >> j & 1, y = b[i] >> j & 1;
        sum[p][0] = sum[p - 1][0];
        sum[p][1] = sum[p - 1][1];
        if (x == y) { dp[p] = dp[p - 1]; continue; }
        sum[p][y] += p;
        int64 cost = x ? t1 : t0;
        dp[p] = dp[p - 1] + cost;
        if (!stk[y ^ 1].empty()) {
          int q = stk[y ^ 1].back();
          auto w = (sum[p][y] - sum[q - 1][y]) - (sum[p][y ^ 1] - sum[q - 1][y ^ 1]);
          if (w <= inf / ts) dp[p] = std::min(dp[p], dp[q - 1] + ts * w);
          stk[y ^ 1].pop_back();
        }
        stk[y].emplace_back(p);
      }
    }
    printf("%lld\n", dp[n * 4]);
  }
  return 0;
}

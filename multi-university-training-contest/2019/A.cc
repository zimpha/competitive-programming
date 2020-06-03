#include <cstdio>
#include <cstring>
#include <vector>

using int64 = long long;
const int N = 110, mod = 998244353;

std::vector<std::pair<int, int>> limit[N];
int mark[N][N][N];
int64 dp[N][N][N];

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i <= n; ++i) {
      limit[i].clear();
    }
    for (int i = 0; i < m; ++i) {
      int l, r, x;
      scanf("%d%d%d", &l, &r, &x);
      limit[r].emplace_back(l, x);
    }
    memset(mark, -1, sizeof(mark));
    memset(dp, 0, sizeof(dp));
    dp[0][0][0] = 1;
    for (int i = 0; i < n; ++i) {
      int  bound = i ? i : i + 1;
      for (int z = 0; z < bound; ++z) {
        for (int y = 0, uy = z - !!z; y <= uy; ++y) {
          for (int x = 0, ux = y - !!y; x <= ux; ++x) if (mark[z][y][x] == i - 1 && (dp[z][y][x] %= mod)) {
            int w = dp[z][y][x];
            if (mark[z][y][x] != i) mark[z][y][x] = i, dp[z][y][x] = 0;
            if (mark[i][z][y] != i) mark[i][z][y] = i, dp[i][z][y] = 0;
            if (mark[i][z][x] != i) mark[i][z][x] = i, dp[i][z][x] = 0;
            if (mark[i][y][x] != i) mark[i][y][x] = i, dp[i][y][x] = 0;
            int a[] = {i + 1, z, y, x, 0};
            int b[] = {i + 1, i, z, y, 0};
            int c[] = {i + 1, i, z, x, 0};
            int d[] = {i + 1, i, y, x, 0};
            int va = 1, vb = 1, vc = 1, vd = 1;
            for (auto &l: limit[i + 1]) {
              if (va && !(a[l.second] < l.first && a[l.second - 1] >= l.first)) va = 0;
              if (vb && !(b[l.second] < l.first && b[l.second - 1] >= l.first)) vb = 0;
              if (vc && !(c[l.second] < l.first && c[l.second - 1] >= l.first)) vc = 0;
              if (vd && !(d[l.second] < l.first && d[l.second - 1] >= l.first)) vd = 0;
            }
            if (va) dp[z][y][x] = w;
            if (vb) dp[i][z][y] += w;
            if (vc) dp[i][z][x] += w;
            if (vd) dp[i][y][x] += w;
          }
        }
      }
    }
    int64 ret = 0;
    for (int z = 0; z < n; ++z) {
      for (int y = 0, uy = z - !!z; y <= uy; ++y) {
        for (int x = 0, ux = y - !!y; x <= ux; ++x) if (mark[z][y][x] == n - 1) {
          ret += dp[z][y][x] % mod;
        }
      }
    }
    printf("%lld\n", ret % mod);
  }
  return 0;
}

#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>

using int64 = long long;

const int N = 200 + 10;
const int64 inf = 1ll << 61;

bool mark[61][N][N];
int64 dp[61][N][N];
int64 s[N], m;
int n;

int64 solve(int x, int l, int r) {
  if (x == -1) assert(l == r);
  if (x == -1) return 0;
  if (mark[x][l][r]) return dp[x][l][r];
  mark[x][l][r] = 1;
  int64 ret = -inf;
  for (int u = 0; u <= r - l + 1; ++u) {
    int v = r - l + 1 - u;
    if (std::max(u, v) > (1ll << x)) continue;
    int64 tmp = 0;
    if (u) tmp += solve(x - 1, l, l + u - 1);
    if (v) tmp += solve(x - 1, l + u, r) + s[r] - s[l + u - 1];
    ret = std::max(ret, tmp);
  }
  return dp[x][l][r] = ret;
}

bool mark2[61][N];
int64 dp2[61][N];

int64 solve2(int x, int l) {
  assert(l <= n);
  if (x == -1 && l != n) return -inf;
  if (x == -1) return 0;
  if (mark2[x][l]) return dp2[x][l];
  mark2[x][l] = 1;
  int64 ret = -inf;
  int o = m >> x & 1;
  if (!o) ret = solve2(x - 1, l);
  else {
    for (int u = 0; u <= n - l + 1; ++u) {
      if ((1ll << x) < u) continue;
      int64 tmp = 0;
      if (u) tmp += solve(x - 1, l, l + u - 1);
      if (u != n - l + 1) {
        if (solve2(x - 1, l + u) == -inf) continue;
        tmp += solve2(x - 1, l + u) + s[n] - s[l + u - 1];
      }
      ret = std::max(ret, tmp);
    }
  }
  return dp2[x][l] = ret;
}

int main() {
  scanf("%d%lld", &n, &m);
  for (int i = 1; i <= n; ++i) {
    scanf("%lld", &s[i]);
    s[i] += s[i - 1];
  }
  memset(mark, 0, sizeof(mark));
  memset(mark2, 0, sizeof(mark2));
  printf("%lld\n", solve2(60, 1));
  return 0;
}

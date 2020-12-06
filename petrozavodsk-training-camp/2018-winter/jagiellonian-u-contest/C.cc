#include <cstdio>
#include <vector>
#include <algorithm>

const int N = 2e5 + 10;

std::pair<int, int> a[N], buffer[N];
int xs[N], bit[N], dp[N];

void solve(int l, int r) {
  if (l + 1 == r) {
    dp[l] += 1;
    return;
  }
  int m = (l + r) >> 1;
  solve(l, m);
  for (int i = l; i < r; ++i) {
    xs[i - l] = a[i].second;
    buffer[i - l] = {a[i].first, -i};
  }
  std::sort(xs, xs + r - l);
  int ns = std::unique(xs, xs + r - l) - xs;
  std::sort(buffer, buffer + r - l);
  for (int i = 0; i <= ns; ++i) bit[i] = 0;
  for (int i = 0; i < r - l; ++i) {
    int e = -buffer[i].second;
    int x = std::lower_bound(xs, xs + ns, a[e].second) - xs;
    if (e < m) {
      for (; x <= ns; x += ~x & x + 1) {
        bit[x] = std::max(bit[x], dp[e]);
      }
    } else {
      for ( x -= 1; x >= 0; x -= ~x & x + 1) {
        dp[e] = std::max(dp[e], bit[x]);
      }
    }
  }
  solve(m, r);
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) scanf("%d", &a[i].first);
    for (int i = 0; i < n; ++i) scanf("%d", &a[i].second);
    for (int i = 0; i < n; ++i) dp[i] = 0;
    solve(0, n);
    int ret = 0;
    for (int i = 0; i < n; ++i) {
      ret = std::max(ret, dp[i]);
    }
    printf("%d\n", ret);
  }
  return 0;
}

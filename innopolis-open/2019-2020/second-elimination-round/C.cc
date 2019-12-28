#include <cstdio>
#include <cstring>
#include <vector>
#include <functional>
#include <algorithm>

const int N = 100, M = 10000;

int dp[N + 1][M + 1];

void update(int &a, int b) {
  if (a == -1 || a > b) a = b;
}

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
  int m;
  scanf("%d", &m);
  std::vector<std::pair<int, int>> b(m);
  for (int i = 0; i < m; ++i) {
    scanf("%d%d", &b[i].first, &b[i].second);
  }
  std::sort(b.begin(), b.end(), [](const std::pair<int, int> &a, const std::pair<int, int> &b) {
    return a.second * b.first > a.first * b.second;
  });
  std::sort(a.begin(), a.end(), std::greater<int>());
  memset(dp, -1, sizeof(dp));
  dp[0][0] = 0;
  int sm = 0;
  for (int i = 0; i < m; ++i) sm += b[i].first;
  for (int i = 0; i < m; ++i) {
    int cost = b[i].first, cnt = b[i].second;
    for (int j = i + 1; j >= 1; --j) {
      for (int k = sm; k >= cost; --k) if (dp[j - 1][k - cost] != -1) {
        update(dp[j][k], dp[j - 1][k - cost] + (k - cost) * cnt);
      }
    }
  }
  std::vector<int> ret(n + m + 1, 0);
  for (int i = 0, sn = 10000; i <= n; ++i) {
    for (int j = 0; j <= m; ++j) {
      for (int k = 0; k <= sm; ++k) if (dp[j][k] != -1) {
        ret[i + j] = std::max(ret[i + j], sn * k - dp[j][k]);
      }
    }
    if (i < n) sn += a[i];
  }
  int q;
  scanf("%d", &q);
  for (int i = 0, x; i < q; ++i) {
    scanf("%d", &x);
    printf("%d\n", ret[x]);
  }
  return 0;
}

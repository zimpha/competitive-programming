#include <cstdio>
#include <vector>
#include <algorithm>

using int64 = long long;
const int N = 17;

int64 cnt[N][N * N];

void prepare() {
  cnt[0][0] = 1;
  for (int i = 1; i < N; ++i) {
    for (int j = 0; j <= i * (i - 1) / 2; ++j) {
      for (int k = 0; k < i && k <= j; ++k) {
        cnt[i][j] += cnt[i - 1][j - k];
      }
    }
  }
}

int64 gcd(int64 x, int64 y) {
  return y ? gcd(y, x % y) : x;
}

int main() {
  prepare();
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, a, b, c, m;
    scanf("%d%d%d%d%d", &n, &a, &b, &c, &m);
    std::vector<int> dp(n * (n - 1) / 2 + 1);
    for (int i = 0; i <= n * (n - 1) / 2; ++i) dp[i] = i * a;
    for (int i = 0; i <= n * (n - 1) / 2; ++i) {
      dp[i] = std::min(i * a, (n * (n - 1) / 2 - i) * a + b);
    }
    std::vector<std::pair<int, int64>> vs(n * (n - 1) / 2 + 1);
    int64 fac = 1;
    for (int i = 1; i <= n; ++i) fac *= i;
    for (int i = 0; i <= n * (n - 1) / 2; ++i) vs[i] = {dp[i], cnt[n][i]};
    std::sort(vs.begin(), vs.end());
    int64 xu = 0, xv = 0;
    for (int i = 0; i < n * (n - 1) / 2; ++i) {
      xu += vs[i].first * vs[i].second;
      xv += vs[i].second;
      if (vs[i].first * xv <= xu + fac * c && vs[i + 1].first * xv >= xu + fac * c) {
        break;
      }
    }
    int64 g = gcd(xu + c * fac, xv);
    xv /= g; xu = (xu + c * fac) / g;
    for (int it = 0; it < m; ++it) {
      int inv = 0;
      std::vector<int> p(n);
      for (int i = 0; i < n; ++i) {
        scanf("%d", &p[i]);
        for (int j = 0; j < i; ++j) inv += p[j] > p[i];
      }
      int now = dp[inv];
      if (now * xv <= xu) printf("%d/1\n", now);
      else printf("%lld/%lld\n", xu, xv);
    }
  }
  return 0;
}

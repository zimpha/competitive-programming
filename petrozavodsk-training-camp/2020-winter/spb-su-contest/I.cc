#include <cstdio>
#include <vector>
#include <algorithm>

using int64 = long long;

const int N = 1e6 + 10;
const int64 inf = 1ll << 60;

std::pair<int64, int64> line[N];
long double x[N];
char s[N];

int main() {
  int n, y;
  scanf("%d%d%s", &n, &y, s);
  std::vector<int> a = {0};
  for (int i = 0, cnt = 0; i < n; ++i) {
    if (s[i] == '+') ++cnt;
    else a.push_back(cnt);
  }
  n = a.size();
  std::vector<int64> sum(n);
  for (int i = 0; i < n; ++i) {
    if (i) sum[i] = sum[i - 1];
    sum[i] += a[i];
  }
  std::vector<int64> dp(n + 1);
  line[0] = {dp[0] + y, a[0]};
  x[0] = -inf;
  int m = 1, p = 0;

  auto add = [&] (int64 a, int64 b) {
    while (m > 0) {
      int64 aa = line[m - 1].first, bb = line[m - 1].second;
      if (b == bb) {
        if (aa > a) {
          m--;
        } else {
          return;				
        }
      } else {
        long double cx = (long double)1.0 * (a - aa) / (b - bb);
        if (x[m - 1] < cx) {
          line[m] = {a, b};
          x[m++] = cx;
          return;	
        } else {
          m--;    	
        }
      }
    }

    line[m++] = {a, b};
  };

  for (int i = 1; i <= n; ++i) {
    p = std::min(p, m - 1);
    while (p < m - 1 && x[p + 1] <= i) ++p;
    dp[i] = line[p].first - line[p].second * i + sum[i - 1];
    add(dp[i] - sum[i - 1] + 1ll * a[i] * i + y, a[i]);
  }
  printf("%lld\n", dp[n] - y);
  return 0;
}

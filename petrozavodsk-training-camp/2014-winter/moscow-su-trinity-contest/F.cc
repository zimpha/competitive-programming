#include <cstdio>
#include <vector>
#include <algorithm>

using int64 = long long;
using pii = std::pair<int64, int64>;

const int N = 2000 + 10;

int64 dp[N][N], s[N];
std::vector<pii> hull[N];
std::vector<double> xs[N];
pii buffer[N];

double inter(const pii &a, const pii &b) {
  return double(b.second - a.second) / (a.first - b.first);
}

int64 query(int i, int64 x) {
  if (hull[i].empty()) return 0;
  int id = std::lower_bound(xs[i].begin(), xs[i].end(), x) - xs[i].begin();
  return hull[i][id].first * x + hull[i][id].second;
}

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%lld", &s[i]);
    s[i] += s[i - 1];
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j < i; ++j) {
      if (j == 0) dp[i][j] = 0;
      else {
        dp[i][j] = query(j, s[j] - s[i]) + (s[i] - s[j]) * s[j];
      }
      buffer[j] = {s[j], dp[i][j]};
    }
    std::sort(buffer, buffer + i);
    int sz = 0;
    for (int j = 0; j < i; ++j) {
      while ((sz >= 1 && hull[i].back().first == buffer[j].first) ||
          (sz >= 2 && inter(hull[i].back(), buffer[j]) <= xs[i].back())) {
        --sz;
        if (sz) xs[i].pop_back();
        hull[i].pop_back();
      }
      hull[i].push_back(buffer[j]); ++sz;
      if (sz >= 2) xs[i].push_back(inter(hull[i][sz - 1], hull[i][sz - 2]));
    }
  }
  int64 ret = 0;
  for (int i = 0; i < n; ++i) {
    ret = std::max(ret, dp[n][i]);
  }
  printf("%lld\n", ret);
  return 0;
}

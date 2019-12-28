#include <cstdio>
#include <vector>
#include <cassert>
#include <algorithm>

using int64 = long long;

const int N = 1e5 + 10;

std::vector<std::pair<int64, int64>> dp[N];

int main() {
  int n;
  int64 s;
  scanf("%d%lld", &n, &s);
  std::vector<int64> a(n), b(n);
  dp[0] = {{0, 0}};
  for (int i = 1; i <= n; ++i) {
    const auto &u = dp[i - 1];
    std::vector<std::pair<int64, int64>> v;
    int64 l, r;
    scanf("%lld%lld", &l, &r);
    a[i - 1] = l;
    b[i - 1] = r;
    for (auto &e: u) {
      v.emplace_back(e.first + l, e.second + r);
    }
    auto add = [&](const std::pair<int64, int64> &t) {
      if (t.first <= r + 1) r = std::max(r, t.second);
      else {
        if (l <= s) dp[i].emplace_back(l, r);
        l = t.first;
        r = t.second;
      }
    };

    size_t x = 0, y = 0;
    l = 0, r = 0;
    for (; x < u.size() && y < v.size(); ) {
      if (u[x].first < v[y].first) add(u[x++]);
      else add(v[y++]);
    }
    while (x < u.size()) add(u[x++]);
    while (y < v.size()) add(v[y++]);
    if (l <= s) dp[i].emplace_back(l, r);
    //for (auto &e: dp[i]) printf("[%lld, %lld] ", e.first, e.second);
    //puts("");
  }
  int64 ret = std::min(s, dp[n].back().second);
  std::vector<int64> w(n);
  printf("%lld\n", ret);
  for (int i = n - 1; i >= 0; --i) {
    for (auto &e: dp[i]) {
      if (e.first + a[i] <= ret && ret <= e.second + b[i]) {
        int64 l = std::max(a[i], ret - e.second);
        int64 r = std::min(b[i], ret - e.first);
        assert(l <= r);
        w[i] = r;
        ret -= r;
        break;
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    printf("%lld ", w[i]);
  }
  return 0;
}

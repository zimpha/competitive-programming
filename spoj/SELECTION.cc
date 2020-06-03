#include <cstdio>
#include <vector>
#include <algorithm>

using int64 = long long;

int main() {
  int n, m, k;
  scanf("%d%d%d", &n, &m, &k);
  std::vector<std::pair<int64, int>> s(n * m);
  for (int i = 0; i < n; ++i) {
    int64 x, a, b, c;
    scanf("%lld%lld%lld%lld", &x, &a, &b, &c);
    for (int j = 0; j < m; ++j) {
      s[i * m + j].first = x;
      s[i * m + j].second = i;
      x = (a * x + b) % c;
    }
  }
  std::vector<int> cnt(n);
  int valid_count = 0;
  std::sort(s.begin(), s.end());
  int64 ret = -1;
  for (size_t i = 0, j = 0; i < s.size(); ++i) {
    while (j < s.size() && valid_count < n) {
      auto w = s[j++].second;
      cnt[w]++;
      if (cnt[w] == k) ++valid_count;
    }
    if (valid_count == n) {
      if (ret == -1 || ret > s[j - 1].first - s[i].first) {
        ret = s[j - 1].first - s[i].first;
      }
    }
    auto w = s[i].second;
    if (cnt[w] == k) --valid_count;
    cnt[w]--;
  }
  printf("%lld\n", ret);
  return 0;
}

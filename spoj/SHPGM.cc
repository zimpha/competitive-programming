#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>

using int64 = long long;

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, m;
    scanf("%d%d", &n, &m);
    std::vector<std::pair<int, std::pair<int, int>>> s;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        int x;
        scanf("%d", &x);
        if (x) s.emplace_back(x, std::make_pair(i, j));
      }
    }
    std::sort(s.begin(), s.end());
    int64 ret = 0;
    for (size_t i = 1; i < s.size(); ++i) {
      ret += abs(s[i].second.first - s[i - 1].second.first);
      ret += abs(s[i].second.second - s[i - 1].second.second);
    }
    printf("Case %d: %lld\n", cas, ret);
  }
  return 0;
}

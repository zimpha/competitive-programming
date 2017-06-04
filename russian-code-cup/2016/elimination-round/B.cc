#include <cstdio>
#include <vector>
#include <algorithm>

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, m;
    scanf("%d%d", &n, &m);
    std::vector<std::pair<int, int>> leg(m);
    std::vector<int> xs;
    for (int i = 0; i < m; ++i) {
      scanf("%d%d", &leg[i].first, &leg[i].second);
      xs.push_back(leg[i].second);
    }
    std::sort(xs.begin(), xs.end());
    xs.erase(std::unique(xs.begin(), xs.end()), xs.end());
    int s = xs.size();
    std::vector<int> bit(s + 1);
    int ret = -1, left = 0;
    std::sort(leg.begin(), leg.end());
    for (auto &&e: leg) {
      int x = std::lower_bound(xs.begin(), xs.end(), e.second) - xs.begin();
      for (; x <= s; x += ~x & x + 1) bit[x] += 1;
      x = std::upper_bound(xs.begin(), xs.end(), n - e.first) - xs.begin() - 1;
      int sum = 0;
      for (; x >= 0; x -= ~x & x + 1) sum += bit[x];
      if (sum > ret) ret = sum, left = e.first;
    }
    printf("%d %d\n", left, n - left);
  }
  return 0;
}

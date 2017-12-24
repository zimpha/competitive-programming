#include <cstdio>
#include <map>
#include <algorithm>
#include <vector>

using int64 = long long;

int main() {
  int q, k;
  scanf("%d%d", &q, &k);
  std::map<std::string, int64> mp;
  for (int i = 0; i < q; ++i) {
    static char buf[100];
    int cost;
    scanf("%s%d", buf, &cost);
    mp[buf] += cost;
  }
  std::vector<int64> cost;
  for (auto &&e: mp) cost.emplace_back(e.second);
  std::sort(cost.begin(), cost.end(), std::greater<int64>());
  int64 ret = 0;
  for (int i = 0; i < k && i < (int)cost.size(); ++i) {
    ret += cost[i];
  }
  printf("%lld\n", ret);
  return 0;
}

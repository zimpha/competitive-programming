#include <cstdio>
#include <vector>
#include <set>
#include <utility>

using int64 = long long;

int main() {
  int n, k;
  scanf("%d%d", &n, &k);
  std::vector<int> c(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &c[i]);
  }
  int64 ret = 0;
  std::set<std::pair<int, int>> can;
  for (int i = 0; i < k; ++i) {
    can.emplace(-c[i], i);
  }
  std::vector<int> dep(n);
  for (int i = k; i < n + k; ++i) {
    if (i < n) {
      can.emplace(-c[i], i);
    }
    int u = can.begin()->second;
    can.erase(can.begin());
    dep[u] = i + 1;
    ret += int64(i - u) * c[u];
  }
  printf("%lld\n", ret);
  for (auto &&x: dep) printf("%d ", x);
  puts("");
  return 0;
}
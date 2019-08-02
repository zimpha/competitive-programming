#include <cstdio>
#include <vector>
#include <algorithm>

int main() {
  int n;
  scanf("%d", &n);
  std::vector<std::pair<int, int>> e;
  for (int i = 0; i < n; ++i) {
    int a, b;
    scanf("%d%d", &a, &b);
    e.emplace_back(a, +1);
    e.emplace_back(b + 1, -1);
  }
  std::sort(e.begin(), e.end());
  int ret = 0, cnt = 0;
  for (auto &&x: e) {
    cnt += x.second;
    ret = std::max(ret, cnt);
  }
  printf("%d\n", ret);
  return 0;
}

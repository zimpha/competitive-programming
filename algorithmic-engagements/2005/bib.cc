#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>

using int64 = long long;

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }
  std::priority_queue<std::pair<int, int>> pq;
  for (int i = 0; i < n; ++i) {
    pq.emplace(-a[i], i + 1);
  }
  int64 ret = 0;
  std::vector<std::pair<int, int>> step;
  while (pq.size() != 1) {
    auto a = pq.top(); pq.pop();
    auto b = pq.top(); pq.pop();
    if (a.second > b.second) std::swap(a, b);
    ret -= a.first + b.first;
    pq.emplace(a.first + b.first, std::min(a.second, b.second));
    step.emplace_back(a.second, b.second);
  }
  printf("%lld\n", ret);
  for (auto &e: step) {
    printf("%d %d\n", e.first, e.second);
  }
  return 0;
}

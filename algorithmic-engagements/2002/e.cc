#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>

int main() {
  int m, n;
  scanf("%d%d", &m, &n);
  std::vector<std::pair<int, int>> s(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d%d", &s[i].second, &s[i].first);
  }
  std::sort(s.begin(), s.end());
  std::reverse(s.begin(), s.end());
  std::priority_queue<int> pq;
  int ret = 0;
  for (int i = 1; i <= m; ++i) {
    while (!s.empty() && s.back().first <= i) {
      pq.push(s.back().second);
      s.pop_back();
    }
    if (!pq.empty()) {
      ret += pq.top();
      pq.pop();
    }
  }
  printf("%d\n", ret);
  return 0;
}

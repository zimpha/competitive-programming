#include <cstdio>
#include <vector>
#include <algorithm>

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    std::vector<std::pair<int, int>> events;
    for (int i = 0; i < n; ++i) {
      int l, r;
      scanf("%d%d", &l, &r);
      events.emplace_back(l, 1);
      events.emplace_back(r, -1);
    }
    std::sort(events.begin(), events.end());
    int cnt = 0, left = 0, ret = -1;
    for (size_t i = 0, j; i < events.size(); i = j) {
      for (j = i; j < events.size() && events[i].first == events[j].first; ++j) cnt += events[j].second, left += events[j].second == -1;
      int right = n - cnt - left;
      if (left && right) {
        if (ret == -1 || ret > cnt) ret = cnt;
      }
    }
    printf("%d\n", ret);
  }
  return 0;
}

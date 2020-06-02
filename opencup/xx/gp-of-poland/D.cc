#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    std::vector<int> s(n);
    std::vector<std::pair<int, int>> events;
    for (int i = 0; i < n; ++i) {
      int r;
      scanf("%d%d", &r, &s[i]);
      int x = std::max(0, i - r);
      int y = std::min(n - 1, i + r);
      events.emplace_back(x, i + 1);
      events.emplace_back(y + 1, -(i + 1));
    }
    std::sort(events.begin(), events.end());
    n = events.size();
    std::multiset<int> v;
    int ret = 0;
    for (int i = 0, j; i < n; i = j) {
      for (j = i; j < n && events[i].first == events[j].first; ++j) {
        int e = std::abs(events[j].second) - 1;
        if (events[j].second < 0) v.erase(v.find(s[e]));
        else v.insert(s[e]);
      }
      if (v.size() >= 3) {
        std::vector<int> u;
        for (int i = 0; i < 3; ++i) {
          u.push_back(*v.rbegin());
          v.erase(v.find(u.back()));
        }
        ret = std::max(ret, u[0] + u[1] + u[2]);
        for (auto &e: u) v.insert(e);
      }
    }
    printf("%d\n", ret);
  }
  return 0;
}

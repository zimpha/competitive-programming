#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>

bool check(std::vector<int> &sa, std::vector<int> &ea, std::vector<int> &sb, std::vector<int> &eb) {
  int n = sa.size();
  std::vector<std::pair<int, int>> events;
  events.reserve(n * 2);
  for (int i = 0; i < n; ++i) {
    events.emplace_back(sb[i], i + 1);
    events.emplace_back(eb[i] + 1, -i - 1);
  }
  std::sort(events.begin(), events.end());

  std::multiset<int> ls, rs;
  for (size_t i = 0, j; i < events.size(); i = j) {
    for (j = i; j < events.size() && events[i].first == events[j].first; ++j) {
      int idx = std::abs(events[j].second) - 1;
      if (events[j].second > 0) ls.insert(sa[idx]), rs.insert(ea[idx]);
      else ls.erase(ls.find(sa[idx])), rs.erase(rs.find(ea[idx]));
    }
    if (!ls.empty()) {
      auto l = *ls.rbegin(), r = *rs.begin();
      if (l > r) return false;
    }
  }
  return true;
}

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> sa(n), ea(n), sb(n), eb(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d%d%d%d", &sa[i], &ea[i], &sb[i], &eb[i]);
  }
  if (check(sa, ea, sb, eb) && check(sb, eb, sa, ea)) puts("YES");
  else puts("NO");
  return 0;
}

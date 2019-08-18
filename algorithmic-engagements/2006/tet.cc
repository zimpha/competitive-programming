#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>

int main() {
  int n;
  scanf("%d", &n);
  std::vector<std::pair<int, int>> a(n);
  std::vector<int> idx(n);
  for (int i = 0; i < n; ++i) {
    idx[i] = i;
    scanf("%d%d", &a[i].second, &a[i].first);
  }
  std::sort(idx.begin(), idx.end(), [&](int x, int y) {
    return a[x] < a[y];
  });
  std::vector<int> prev(n, -1);
  std::set<std::pair<int, int>> s;
  for (int i = 0; i < n; ++i) {
    int l = a[idx[i]].first;
    int r = l + a[idx[i]].second;
    auto it = s.upper_bound(std::make_pair(l, n));
    if (it != s.begin()) {
      --it;
      prev[idx[i]] = it->second;
      s.erase(it);
    } 
    s.emplace(r, idx[i]);
  }
  std::vector<int> ret;
  for (auto &e: s) {
    for (int x = e.second; x != -1; x = prev[x]) {
      ret.push_back(x);
    }
  }
  printf("%d\n", (int)s.size());
  for (int i = 0; i < n; ++i) {
    printf("%d\n", ret[i] + 1);
  }
  return 0;
}

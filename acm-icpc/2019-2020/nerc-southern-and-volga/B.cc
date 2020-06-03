#include <cstdio>
#include <cstring>
#include <vector>
#include <set>
#include <algorithm>

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  std::vector<int> cnt(m);
  for (int i = 0, x; i < n; ++i) {
    scanf("%d", &x);
    cnt[x - 1]++;
  }
  std::vector<int> a;
  for (auto &x: cnt) {
    if (x) a.push_back(x);
  }
  std::sort(a.begin(), a.end());
  std::vector<int> mark(n + 1);
  for (auto &x: a) mark[x] = 1;
  for (size_t i = 0; i < a.size(); ++i) {
    for (size_t j = 0; j < i; ++j) {
      mark[a[i] + a[j]] = 1;
    }
  }
  int ret = -1;
  for (int s = 1; s <= n; ++s) if (mark[s]) {
    if (s < a.back()) continue;
    std::multiset<int> all(a.begin(), a.end());
    int r = 0;
    while (!all.empty()) {
      ++r;
      int u = *all.rbegin();
      all.erase(all.find(u));
      if (all.empty()) break;
      auto it = all.upper_bound(s - u);
      if (it != all.begin()) {
        --it;
        all.erase(it);
      }
    }
    if (ret == -1 || r * s < ret) ret = r * s;
  }
  printf("%d\n", ret);
  return 0;
}

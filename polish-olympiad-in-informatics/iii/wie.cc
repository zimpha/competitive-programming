#include <cstdio>
#include <set>
#include <vector>
#include <algorithm>

const int N = 3000 + 10;

std::vector<int> enter[N], leave[N];

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> a(n), b(n), c(n), d(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d%d%d%d", &a[i], &c[i], &b[i], &d[i]);
  }
  std::vector<int> x(n, -1), y(n, -1);
  std::multiset<std::pair<int, int>> s;
  for (int i = 0; i < n; ++i) enter[a[i]].push_back(i);
  for (int i = 0; i < n; ++i) leave[b[i]].push_back(i);
  for (int i = 1; i <= n; ++i) {
    for (auto &&p: enter[i]) s.emplace(b[p], p);
    enter[i].clear();
    if (s.empty()) {
      puts("NIE");
      return 0;
    }
    x[s.begin()->second] = i;
    s.erase(s.begin());
    for (auto &&p: leave[i]) {
      auto it = s.find({b[p], p});
      if (it != s.end()) s.erase(it);
    }
    leave[i].clear();
  }
  s.clear();
  for (int i = 0; i < n; ++i) enter[c[i]].push_back(i);
  for (int i = 0; i < n; ++i) leave[d[i]].push_back(i);
  for (int i = 1; i <= n; ++i) {
    for (auto &&p: enter[i]) s.emplace(d[p], p);
    if (s.empty()) {
      puts("NIE");
      return 0;
    }
    y[s.begin()->second] = i;
    s.erase(s.begin());
    for (auto &&p: leave[i]) {
      auto it = s.find({d[p], p});
      if (it != s.end()) s.erase(it);
    }
  }
  for (int i = 0; i < n; ++i) {
    printf("%d %d\n", x[i], y[i]);
  }
  return 0;
}

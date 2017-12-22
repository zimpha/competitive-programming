#include <cstdio>
#include <vector>
#include <set>

int main() {
  int n, m;
  std::scanf("%d%d", &n, &m);
  std::vector<int> cnt(n);
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      int x;
      scanf("%d", &x);
      cnt[j] += x;
    }
    std::set<int> s = {0};
    int x = 0;
    for (int j = 0; j < n; ++j) {
      x += cnt[j];
      if (s.count(x - 777)) {
        puts("YES");
        return 0;
      }
      s.insert(x);
    }
  }
  puts("NO");
  return 0;
}

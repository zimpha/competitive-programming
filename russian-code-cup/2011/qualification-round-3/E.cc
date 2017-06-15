#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>

int main() {
  int n, k;
  scanf("%d", &n);
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }
  scanf("%d", &k);
  std::vector<int> b = a;
  std::sort(b.begin(), b.end());
  std::vector<std::pair<int, int>> res;
  std::vector<std::deque<int>> q(k);
  for (int i = 0, now = 0; i < n; ) {
    bool find = false;
    for (int j = 0; j < k && !find; ++j) {
      if (!q[j].empty() && q[j].front() == b[i]) {
        res.emplace_back(-1, j);
        q[j].pop_front();
        ++i;
        find = true;
      }
    }
    if (find) continue;
    if (now == n) break;
    int best = -1, val = -1;
    for (int j = 0; j < k; ++j) {
      int tv = q[j].empty() ? -1 : q[j].back();
      if (tv <= a[now] && (best == -1 || tv > val)) {
        best = j;
        val = tv;
      }
    }
    if (best == -1) break;
    q[best].push_back(a[now++]);
    res.emplace_back(1, best);
  }
  if (res.size() != 2 * n) puts("NO");
  else {
    puts("YES");
    for (auto &&e: res) {
      if (e.first == 1) printf("I(%d)\n", e.second + 1);
      else printf("R(%d)\n", e.second + 1);
    }
  }
  return 0;
}

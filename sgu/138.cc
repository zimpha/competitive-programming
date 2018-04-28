#include <cstdio>
#include <vector>
#include <functional>
#include <algorithm>

int main() {
  int n;
  scanf("%d", &n);
  std::vector<std::pair<int, int>> cnt(n);
  int sum = 0;
  for (int i = 0; i < n; ++i) {
    scanf("%d", &cnt[i].first);
    cnt[i].second = i + 1;
    sum += cnt[i].first;
  }
  sum /= 2;
  std::sort(cnt.begin(), cnt.end(), std::greater<std::pair<int, int>>());
  std::vector<std::pair<int, int>> res(sum);
  for (int i = 0, m = 0; i < n && m < sum; ++i) {
    int num = cnt[i].first;
    for (int j = 1; j < num && m < sum; ++j) {
      res[m++].first = cnt[i].second;
      --cnt[i].first;
    }
    if (num > 1 && m == sum - 1) {
      res[m++].first = cnt[i].second;
      --cnt[i].first;
    } else if (m < sum) {
      res[m].second = cnt[i].second;
      --cnt[i].first;
    }
  }
  for (int i = 0, j = 0; i < n; ++i) {
    for (int it = 0; it < cnt[i].first; ++it) {
      while (j < sum && res[j].second) ++j;
      res[j].second = cnt[i].second;
    }
  }
  printf("%d\n", (int)res.size());
  for (auto &&e: res) {
    printf("%d %d\n", e.first, e.second);
  }
  return 0;
}

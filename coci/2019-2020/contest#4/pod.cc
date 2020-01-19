#include <cstdio>
#include <vector>
#include <algorithm>

int main() {
  int n;
  scanf("%d", &n);
  std::vector<std::pair<int, int>> s(n);
  long long sum = 0;
  for (int i = 0; i < n; ++i) {
    int x, y;
    scanf("%d%d", &x, &y);
    sum += x;
    s[i] = {y, i};
  }
  std::sort(s.begin(), s.end());
  int ret = 0;
  for (int i = n - 1; i >= 0; --i) {
    if (s[i].first <= sum) sum -= s[i].first;
    else s[i].first = sum, sum = 0;
    ret += s[i].first == 0;
  }
  std::sort(s.begin(), s.end(), [](const std::pair<int, int> &x, const std::pair<int, int> &y) {
    return x.second < y.second;
  });
  printf("%d\n", ret);
  for (int i = 0; i < n; ++i) printf("%d ", s[i].first);
  puts("");
  return 0;
}

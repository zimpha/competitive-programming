#include <cstdio>
#include <vector>
#include <algorithm>

int solve(const std::vector<int>& h, int n, int k) {
  std::vector<int> cost(n);
  for (int i = 0; i < n; ++i) {
    if (i == n - 1 || h[i] >= h[i + 1]) cost[i] = 0;
    else cost[i] = h[i + 1] - h[i];
  }
  int ret = 1;
  for (int i = 0, cnt = 0, j = 0; i < n; ++i) {
    if (j < i) j = i;
    while (j < n && cnt + cost[j] <= k) {
      cnt += cost[j++];
    }
    if (j == n && j - i > ret) ret = j - i;
    if (j != n && j - i + 1 > ret) ret = j - i + 1;
    if (i != j) cnt -= cost[i];
  }
  return ret;
}

int main() {
  int n, k;
  scanf("%d%d", &n, &k);
  std::vector<int> h(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &h[i]);
  }
  int ret = solve(h, n, k);
  std::reverse(h.begin(), h.end());
  ret = std::max(ret, solve(h, n, k));
  printf("%d\n", ret);
  return 0;
}

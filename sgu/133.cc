#include <cstdio>
#include <utility>
#include <vector>
#include <algorithm>

int main() {
  int n;
  scanf("%d", &n);
  std::vector<std::pair<int, int>> iv(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d%d", &iv[i].first, &iv[i].second);
  }
  std::sort(iv.begin(), iv.end());
  int mx = -1, ret = 0;
  for (int i = 0, j; i < n; i = j) {
    for (j = i; j < n && iv[i].first == iv[j].first; ++j) {
      ret += mx > iv[j].second;
    }
    for (int k = i; k < j; ++k) {
      mx = std::max(mx, iv[k].second);
    }
  }
  printf("%d\n", ret);
  return 0;
}

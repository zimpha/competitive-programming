#include <cstdio>
#include <vector>
#include <functional>
#include <algorithm>

using int64 = long long;

const int64 inf = 1ll << 60;

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> s(n);
  std::vector<int64> val(n);
  for (int i = 0; i < n; ++i) {
    char col[10];
    scanf("%s%lld", col, &val[i]);
    if (col[0] == 'R') s[i] = 0;
    if (col[0] == 'G') s[i] = 1;
    if (col[0] == 'B') s[i] = 2;
  }
  for (int i = 1; i < n; ++i) val[i] += val[i - 1];
  int64 ret = -inf;
  for (int i = 0, j; i < n; i = j) {
    for (j = i + 1; j < n && s[j] != s[j - 1]; ++j);
    int64 best[3] = {inf, inf, inf};
    for (int k = i; k < j; ++k) {
      best[s[k]] = std::min(best[s[k]], k ? val[k - 1] : 0);
      for (int t = 0; t < 3; ++t) {
        if (t != s[k]) ret = std::max(ret, val[k] - best[t]);
      }
    }
  }
  if (ret < -inf / 10) puts("Impossible");
  else printf("%lld\n", ret);
  return 0;
}

#include <cstdio>
#include <vector>
#include <tuple>

using int64 = long long;

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> a(n - 1);
  for (int i = 0; i < n - 1; ++i) scanf("%d", &a[i]);
  std::vector<std::pair<int, int>> missing;
  int best = 0, bound = -1;
  for (int i = 0; i < n - 1; ++i) {
    if (a[i] > best) {
      if (a[i] != best + 1) {
        for (int j = best + 1; j < a[i]; ++j) missing.emplace_back(bound, i);
      } else bound = i;
      best = a[i];
    }
  }
  if (missing.size() > 1) {
    puts("0");
    return 0;
  }
  if (missing.size() == 1) {
    printf("%d\n", missing[0].second - missing[0].first);
  } else {
    best = 0;
    int64 ret = 0;
    for (int i = 0; i < n - 1; ++i) {
      ret += best + 1;
      if (i && a[i - 1] <= best + 1) --ret;
      if (best + 1 == a[i]) ++best;
    }
    ret += best;
    printf("%lld\n", ret);
  }
  return 0;
}

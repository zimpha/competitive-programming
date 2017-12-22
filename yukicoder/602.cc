#include <cstdio>
#include <vector>
#include <algorithm>

int main() {
  int n, x, y;
  scanf("%d", &n);
  std::vector<int> d(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &d[i]);
  }
  scanf("%d%d", &x, &y);
  std::sort(d.begin(), d.end());
  int ret = -1, target = std::abs(x) + std::abs(y);
  int odd = 0, even = 0;
  if (!target) ret = 0;
  for (int i = 0; i < n && target; ++i) {
    if (target == d[i]) {
      ret = 1;
      break;
    }
    if (d[i] & 1) odd = d[i];
    else even = d[i];
    int rest = std::abs(target - d[i]);
    if (rest & 1) {
      if (rest <= odd) ret = 2;
    } else {
      if (rest <= even) ret = 2;
    }
  }
  printf("%d\n", ret);
  return 0;
}

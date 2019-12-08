#include <cstdio>
#include <vector>
#include <algorithm>

using int64 = long long;

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> b(n);
  int64 ret = 0;
  for (int i = 0; i < n; ++i) {
    int x, y;
    scanf("%d%d", &x, &y);
    ret += x;
    b[i] = x + y;
  }
  std::sort(b.begin(), b.end());
  std::reverse(b.begin(), b.end());
  for (int i = 1; i < n; i += 2) ret -= b[i];
  printf("%lld\n", ret);
  return 0;
}


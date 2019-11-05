#include <cstdio>
#include <cassert>
#include <algorithm>

using int64 = long long;

int64 sqr(int64 x) { return x * x; }

int main() {
  int n, a, b, r;
  scanf("%d%d%d%d", &n, &a, &b, &r);
  assert(1 <= n && n <= 100000);
  assert(0 <= r && r <= 1000000000);
  assert(0 <= std::abs(a) && std::abs(a) <= 1000000000);
  assert(0 <= std::abs(b) && std::abs(b) <= 1000000000);
  int ret = 0;
  for (int i = 0; i < n; ++i) {
    int x, y;
    scanf("%d%d", &x, &y);
    assert(0 <= std::abs(x) && std::abs(x) <= 1000000000);
    assert(0 <= std::abs(y) && std::abs(y) <= 1000000000);
    auto d = sqr(x - a) + sqr(y - b);
    ret += d <= sqr(r);
  }
  printf("%d\n", ret);
  return 0;
}

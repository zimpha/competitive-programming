#include <cstdio>
#include <vector>
#include <algorithm>

using int64 = long long;

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> a(n), b(n);
  for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
  for (int i = 0; i < n; ++i) scanf("%d", &b[i]);
  int64 ret = 0;
  for (int i = 0; i < n; ++i) ret += std::abs(a[i] - b[i]);

  auto close = [&](int x1, int x2, int x) {
    if (std::abs(x - x1) <= std::abs(x - x2)) return x1;
    else return x2;
  };

  a.push_back(2e9 + 10);
  std::vector<int> ops, stk;
  for (int i = 0; i < n; ++i) {
    if (stk.empty()) {
      if (close(a[i], a[i + 1], b[i]) == a[i]) ops.push_back(i);
      else stk.push_back(i);
    } else {
      if (b[i] <= a[i] && close(a[stk.back()], a[i], b[i]) == a[i]) {
        ops.push_back(i);
        while (!stk.empty() && close(a[stk.back()], a[i + 1], b[stk.back()]) == a[stk.back()]) {
          ops.push_back(stk.back());
          stk.pop_back();
        }
      } else if (b[i] > a[i] && close(a[i], a[i + 1], b[i]) == a[i]) {
        ops.push_back(i);
        while (!stk.empty() && close(a[stk.back()], a[i + 1], b[stk.back()]) == a[stk.back()]) {
          ops.push_back(stk.back());
          stk.pop_back();
        }
      } else stk.push_back(i);
    }
  }
  printf("%lld\n", ret);
  for (int i = 0; i < n; ++i) printf("%d ", ops[i] + 1);
  puts("");
  return 0;
}

#include <cstdio>
#include <vector>
#include <algorithm>

void rev(std::vector<int> &a, int x) {
  for (int i = x - 1; i <= x + 1; ++i) {
    if (i >= 0 && i < a.size()) a[i] ^= 1;
  }
}

int solve(std::vector<int> a, int x, int y) {
  int ret = 0;
  if (x) ++ret, rev(a, 0);
  for (int i = 0; i < a.size() - 1; ++i) {
    if (a[i] != y) ++ret, rev(a, i + 1);
  }
  if (a.back() != y) return a.size() + 1;
  else return ret;
}

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> a(n), b(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
    a[i] &= 1;
  }
  int o = std::min(solve(a, 0, 1), solve(a, 1, 1));
  int e = std::min(solve(a, 0, 0), solve(a, 1, 0));
  if (o > n) o = -1;
  if (e > n) e = -1;
  printf("%d\n%d\n", o, e);
  return 0;
}

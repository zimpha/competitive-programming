#include <cstdio>
#include <vector>

int solve(int d, std::vector<int> &a) {
  if (d < 0) return 0;
  std::vector<int> l, r;
  for (auto &x: a) {
    if (x >> d & 1) r.push_back(x);
    else l.push_back(x);
  }
  if (l.size() == 0) return solve(d - 1, r);
  if (r.size() == 0) return solve(d - 1, l);
  return std::min(solve(d - 1, l), solve(d - 1, r)) + (1 << d);
}

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
  printf("%d\n", solve(30, a));
  return 0;
}

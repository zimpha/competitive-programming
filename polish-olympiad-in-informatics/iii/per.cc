#include <cstdio>
#include <vector>

std::vector<int> solve(int n) {
  if (n == 1) return {1};
  auto p = solve(n / 2);
  auto q = solve(n - n / 2);
  for (auto &&x : p) x *= 2;
  for (auto &&x : q) p.push_back(x * 2 - 1);
  return p;
}

int main() {
  int n;
  scanf("%d", &n);
  auto p = solve(n);
  for (auto && x: p) printf("%d\n", x - 1);
  return 0;
}

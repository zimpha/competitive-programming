#include <bits/stdc++.h>

using LL = long long;

std::map<std::vector<int>, LL> cache;

LL dfs(int a, int b, int c, int d, int e) {
  if (a < 0 || b < 0 || c < 0 || d < 0 || e < 0) return 0;
  if (a + b + c + d + e == 0) return 1;
  auto x = {a, b, c, d, e};
  if (cache.count(x)) return cache[x];
  return cache[x] = dfs(b, c, d, e, a - 1) + dfs(e - 1, a, b, c, d);
}

LL run(int n) {
  int x = n / 5;
  //cache.clear();
  return dfs(x, x, x, x, x);
}

int main() {
  std::cout << run(25) << std::endl;
  std::cout << run(70) << std::endl;
  return 0;
}

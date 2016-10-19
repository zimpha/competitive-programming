#include <bits/stdc++.h>

long long dfs(int a, int b, int c, int d, int n) {
  int x = a + c, y = b + d, m = y - x;
  if (y > n) return 0;
  long long ret = 0;
  for (int g = 1, upp = n / y; g <= upp; ++g) {
    int x1 = g * x, x2 = g * y;
    if (x1 + x2 & 1) continue;
    int l = std::max((x2 + x - 1) / x, (3 * x1 - x2 + m - 1) / m), r = (n + x1) / y;
    if (l <= r) {
      if (g % 2 == 1) ret += r - l + 1 - (r / 2 - (l - 1) / 2);
      else ret += r / 2 - (l - 1) / 2;
    } else break;
  }
  return ret + dfs(a, b, x, y, n) + dfs(x, y, c, d, n);
}

int main() {
  std::cout << dfs(0, 1, 1, 1, 10) << std::endl;
  std::cout << dfs(0, 1, 1, 1, 50) << std::endl;
  std::cout << dfs(0, 1, 1, 1, 100000) << std::endl;
  return 0;
}

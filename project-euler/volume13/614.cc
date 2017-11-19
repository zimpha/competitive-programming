#include <cmath>
#include <iostream>
#include <vector>

using int64 = long long;

const int mod = 1e9 + 7;

void add(int &x, int y) {
  x += y;
  if (x >= mod) x -= mod;
}

int64 S(int n) {
  std::vector<int> odd(n + 1), even(n + 1);
  std::vector<int> f(n + 1), g(n + 1);
  for (int i = 0; i <= n; ++i) f[i] = 0;
  f[0] = odd[0] = even[0] = 1;
  int m = sqrt(n) * 2;
  for (int i = 1; i <= m; ++i) {
    g.assign(n + 1, 0);
    for (int j = i * 2 - 1; j <= n; ++j) {
      g[j] = f[j - i * 2 + 1];
      if (j >= i * 2) add(g[j], g[j - i * 2]);
      add(odd[j], g[j]);
    }
    f.swap(g);
  }
  for (int i = 1; i <= n; ++i) {
    add(odd[i], odd[i - 1]);
  }
  for (int i = 0; i <= n; ++i) f[i] = 0;
  f[0] = 1;
  for (int i = 1; i <= m; ++i) {
    g.assign(n + 1, 0);
    for (int j = i; j <= n; ++j) {
      g[j] = (f[j - i] + g[j - i]) % mod;
      add(even[j], g[j]);
    }
    f.swap(g);
  }
  int ret = 0;
  for (int x = 0; x * 4 <= n; ++x) {
    add(ret, (int64)even[x] * odd[n - x * 4] % mod);
  }
  return (ret + mod - 1) % mod;
}

int main() {
  std::cout << S(1) << std::endl;
  std::cout << S(2) << std::endl;
  std::cout << S(3) << std::endl;
  std::cout << S(6) << std::endl;
  std::cout << S(10) << std::endl;
  std::cout << S(100) << std::endl;
  std::cout << S(1000) << std::endl;
  std::cout << S(10000000) << std::endl;
  return 0;
}

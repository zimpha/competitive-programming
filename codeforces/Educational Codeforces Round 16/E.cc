#include <bits/stdc++.h>
using LL = long long;

void run() {
  int n, x, y;
  std::cin >> n >> x >> y;
  std::vector<LL> f(n + 3, 1ll << 60);
  f[0] = 0;
  for (int i = 0; i <= n; ++i) {
    f[i] = std::min(f[i], f[i + 1] + x);
    f[i + 1] = std::min(f[i + 1], f[i] + x);
    if (i * 2 <= n + 2) {
      f[i * 2] = std::min(f[i * 2], f[i] + y);
    }
  }
  std::cout << f[n] << std::endl;
}

int main() {
  run();
  return 0;
}

#include <bits/stdc++.h>

using LL = long long;

std::vector<int> mu, pl;

std::map<LL, LL> cache;

LL count(LL n) {
  // #{(x, y): x^2 + y^2 <= n, 0 < x < y}
//  if (cache.count(n)) return cache[n];
  LL ret = 0;
  for (int x = 1; ; ++x) {
    int y = sqrt(n - 1ll * x * x);
    if (y <= x) break;
    ret += y - x;
  }
  return ret;
  //return cache[n] = ret;
}

LL calc(LL n) {
  LL ret = 0;
  int m = sqrt(n);
  for (int i = 1; i <= m; ++i) {
    ret += mu[i] * count(n / i / i);
  }
  return ret;
}

LL run(LL n) {
  int m = sqrt(n) + 1;
  mu.assign(m, 1);
  pl.clear();
  std::vector<bool> vis(m, 1);
  for (int i = 2; i < m; ++i) {
    if (vis[i]) pl.push_back(i), mu[i] = -1;
    for (size_t j = 0; j < pl.size() && i * pl[j] < m; ++j) {
      vis[i * pl[j]] = false;
      if (i % pl[j]) mu[i * pl[j]] = -mu[i];
      else mu[i * pl[j]] = 0;
      if (i % pl[j] == 0) break;
    }
  }
  LL ret = 0, sgn = 1;
  for (LL s = 1; s <= n; s <<= 1) {
    ret += sgn * calc(n / s);
    sgn = -sgn;
  }
  return ret;
}

int main() {
  std::cout << run(20) << std::endl;
  std::cout << run(100000) << std::endl;
  std::cout << run(1000000) << std::endl;
  std::cout << run(3141592653589793ll) << std::endl;
  return 0;
}

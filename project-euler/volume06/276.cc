#include <bits/stdc++.h>
using LL = long long;

const int N = 10000000 + 10;

LL f[N]; //https://oeis.org/A005044

std::map<int, LL> cache;

LL solve(int n) {
  if (cache.count(n)) return cache[n];
  LL ret = f[n];
  for (int g = 2, h; g <= n; g = h + 1) {
    h = n / (n / g);
    ret -= solve(n / g) * (h - g + 1);
  }
  return cache[n] = ret;
}

LL run(int n) {
  for (int i = 1; i <= n; ++i) {
    f[i] = (1ll * i * i + 6) / 12 - 1ll * (i / 4) * ((i + 2) / 4);
    f[i] += f[i - 1];
  }
  return solve(n);
}

int main() {
  std::cout << run(10000000) << std::endl;
  return 0;
}

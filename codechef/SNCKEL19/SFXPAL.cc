#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#include <iostream>

using int64 = long long;

int64 mod;

int64 solve(int64 n, int64 m) {
  if (n == 1) return m % mod;
  else if (n == 2) return m * (m - 1) % mod;
  else return solve(n - 2, m - 1) * m % mod * (m - 1) % mod;
}

int main() {
  int64 n, m;
  scanf("%lld%lld%lld", &n, &m, &mod);
  printf("%lld\n", solve(n, m));
  return 0;
}
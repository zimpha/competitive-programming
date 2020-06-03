#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <vector>
#include <set>

using int64 = long long;

const int mod = 998244353;

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int64> f(n + 1, 1);
  for (int i = 1; i <= n; ++i) f[i] = f[i - 1] * i % mod;
  int64 ret = f[n], p = n;
  for (int i = 1; i <= n; ++i) {
    ret += f[n] - p;
    p = p * (n - i) % mod;
  }
  ret %= mod;
  ret += mod;
  ret %= mod;
  printf("%lld\n", ret);
  return 0;
}
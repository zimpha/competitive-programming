#include <bits/stdc++.h>
using LL = long long;

const LL lim = 1000000000000000000ll;

std::set<int> mp;
LL dfs(LL n, LL x, LL y) {// x / y * n / sigma(n) = 1
  if (n > lim) return 0;
  if (x == 1 && y == 1) {
    std::cout << n << std::endl;
    return n;
  }
  if (y == 1) return 0;
  int p = 2;
  while (y % p && p < 1000) ++p;
  if (mp.count(p)) return 0;
  if (p == 1000) return 0;
  mp.insert(p);
  LL pw = 1, ret = 0;
  for (int e = 1; e <= 20; ++e) {
    pw *= p;
    if (n > lim / pw) break;
    LL nn = n * pw;
    LL xx = x * pw, yy = y * (pw * p - 1) / (p - 1);
    LL g = std::__gcd(xx, yy);
    xx /= g, yy /= g;
    if (yy % p == 0) continue;
    ret += dfs(nn, xx, yy);
  }
  mp.erase(p);
  return ret;
}

LL run() {
  LL ret = 0;
  for (int k = 1; k <= 7; ++k) {
    mp.clear();
    ret += dfs(1, k * 2 + 1, 2);
  }
  return ret;
}

int main() {
  std::cout << run() << std::endl;
}

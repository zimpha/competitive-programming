#include <bits/stdc++.h>

using LL = long long;

LL run(LL p, LL q, LL r) {
  LL m = 1;
  for (int i = 0; i < r; ++i) m *= p;
  std::vector<LL> s = {290797};
  for (int i = 1; i <= q; ++i) {
    s.push_back(s.back() * s.back() % 50515093);
  }
  for (auto &&x: s) x %= p;
  __int128 pw = 0, ret = 0;
  for (int n = q; n >= 1; --n) {
    pw = (pw * p + s[n]) % m;
    ret += pw;
    ret %= m;
  }
  return ret;
}

int main() {
  std::cout << run(3, 10000, 20) << std::endl;
  std::cout << run(61, 10000000, 10) << std::endl;
  return 0;
}


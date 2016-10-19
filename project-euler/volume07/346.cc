#include <bits/stdc++.h>

using LL = long long;

LL run(LL n) {
  LL ret = 0;
  std::map<LL, int> mp;
  --n;
  for (LL b = 2; b * b <= n; ++b) {
    __int128 pw = 1;
    while (true) {
      pw *= b;
      if (pw - 1 > (__int128)n * (b - 1)) break;
      mp[(pw - 1) / (b - 1)]++;
    }
  }
  for (auto &&x: mp) {
    if (x.second > 1 || x.first - 1 > sqrt(n)) {
      ret += x.first;
      //std::cout << x.first << ' ';
    }
  }
  return ret;
}

int main() {
  std::cout << run(50) << std::endl;
  std::cout << run(1000) << std::endl;
  std::cout << run(1000000000000ll) << std::endl;
  return 0;
}

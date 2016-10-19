#include <bits/stdc++.h>

using LL = long long;

LL run(int n) {
  std::map<LL, int> mp;
  mp[0] = 1;
  for (--n; n; ) {
    auto it = mp.begin();
    int split = std::min(n, it->second);
    it->second -= split;
    n -= split;
    mp[it->first + 1] += split;
    mp[it->first + 4] += split;
    if (it->second == 0) mp.erase(it);
  }
  LL ret = 0;
  for (auto &&x: mp) ret += x.first * x.second;
  return ret;
}

int main() {
  assert(run(6) == 35);
  std::cout << run(1000000000) << std::endl;
  return 0;
}

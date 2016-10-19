#include <bits/stdc++.h>
using LL = long long;

LL run(int n) {
  std::vector<int> mp(n + 1, 0);
  for (int i = 2; i <= n; ++i) if (!mp[i]) {
    for (int j = i; j <= n; j += i) mp[j] = i;
  }
  std::map<std::pair<int, int>, int> S;
  for (int i = 2; i <= n; ++i) {
    int m = i, x = mp[m], y;
    while (m != 1 && mp[m] == x) m /= x;
    y = mp[m];
    while (m != 1 && mp[m] == y) m /= y;
    if (x > 1 && y > 1 && m == 1) {
      if (x > y) std::swap(x, y);
      S[{x, y}] = i;
    }
  }
  LL ret = 0;
  for (auto &&x: S) ret += x.second;
  return ret;
}

int main() {
  std::cout << run(100) << std::endl;
  std::cout << run(10000000) << std::endl;
  return 0;
}

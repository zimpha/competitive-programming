#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
#include <cassert>

using int64 = long long;

const int N = 1e6 + 10;

char s[N];

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int64> l(n);
  for (int i = 0; i < n; ++i) scanf("%lld", &l[i]);
  scanf("%s", s);
  int64 grass = 0, water = 0;
  int64 ng = 0, nw = 0;
  int64 sum_grass = 0, sum_water = 0, sum_lava = 0;
  for (int i = 0; i < n; ++i) {
    if (s[i] == 'G') sum_grass += l[i], grass += l[i];
    else if (s[i] == 'W') sum_water += l[i], water += l[i];
    else {
      sum_lava += l[i];
      int64 e = std::min(l[i], grass);
      ng += e;
      grass -= e;
      l[i] -= e;
      e = std::min(l[i], water);
      water -= e;
      l[i] -= e;
      nw += e;
    }
  }
  printf("%lld\n", sum_lava + grass + water + (sum_water - water) / 3 + (sum_grass - grass) / 5)
  return 0;
}
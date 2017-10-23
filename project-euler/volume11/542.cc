#include <cstdio>
#include <map>
#include <algorithm>

using int64 = long long;

int64 T(int64 n) {
  std::map<int64, int64> mp;
  for (int a = 1; a <= 200; ++a) {
    for (int b = 2; b <= 200; ++b) {
      int64 k = a * b, p1 = b * b, p2 = (b - 1) * (b - 1);
      for (int it = 2; k <= n / b; ++it) {
        k *= b;
        p1 *= b;
        p2 *= b - 1;
        int64 v = a * (p1 - p2);
        mp[k] = std::max(mp[k], v);
      }
    }
  }
  int64 now = 0, ret = 0;
  for (auto &&e: mp) if (e.second > now) {
    if (e.first % 2 == 0) ret += e.second - now;
    now = e.second;
  }
  if (n & 1) ret -= now;
  return ret;
}

int main() {
  printf("%lld\n", T(1000));
  printf("%lld\n", T(100000000000000000ll));
}

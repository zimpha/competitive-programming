#include <cstdio>
#include <map>

using int64 = long long;

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int64 n, k;
    scanf("%lld%lld", &n, &k);
    std::map<int64, int64> map;
    map[n] = 1;
    while (k > 0) {
      int64 l = map.rbegin()->first;
      int64 c = map.rbegin()->second;
      map.erase(l);
      if (c >= k) {
        printf("Case #%d: %lld %lld\n", cas, l / 2, l - 1 - l / 2);
        break;
      }
      k -= c;
      int64 a = l / 2;
      int64 b = l - 1 - l / 2;
      if (a > 0) map[a] += c;
      if (b > 0) map[b] += c;
    }
  }
  return 0;
}

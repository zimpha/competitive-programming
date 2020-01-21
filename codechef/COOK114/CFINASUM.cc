#include <cstdio>
#include <vector>
#include <map>

using int64 = long long;

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    std::vector<int> a(n);
    int64 sum = 0;
    for (int i = 0; i < n; ++i) {
      scanf("%d", &a[i]);
      sum += a[i];
    }
    std::map<int64, int> mp;
    int64 s = 0, ret = 0;
    for (int i = 0; i < n; ++i) {
      auto tmp = sum - a[i];
      if (tmp % 2 == 0 && mp.count(tmp / 2)) ret += mp[tmp / 2];
      s += a[i];
      mp[s]++;
    }
    mp.clear(); s = 0;
    for (int i = n - 1; i >= 0; --i) {
      auto tmp = sum - a[i];
      if (tmp % 2 == 0 && mp.count(tmp / 2)) ret += mp[tmp / 2];
      s += a[i];
      mp[s]++;
    }
    printf("%lld\n", ret);
  }
  return 0;
}

#include <bits/stdc++.h>

using ll = long long;

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int a, b;
    scanf("%d%d", &a, &b);
    ll ra = a, rb = b;
    std::map<int, int> mp;
    for (int i = 2; i * i <= a; ++i) {
      while (a % i == 0) mp[i] += 1, a /= i;
    }
    if (a > 0) mp[a] += 1;
    for (int i = 2; i * i <= b; ++i) {
      while (b % i == 0) mp[i] += 1, b /= i;
    }
    if (b > 0) mp[b] += 1;
    std::vector<int> pl;
    for (auto &&x: mp) {
      if (x.second & 1) pl.push_back(x.first);
    }
    int m = pl.size();
    for (int mask = 0; mask < (1 << m); ++mask) {
      ll a = 1, b = 1;
      for (int i = 0; i < m; ++i) {
        if (mask >> i & 1) a *= pl[i];
        else b *= pl[i];
      }
      if (a + b < ra + rb) {
        ra = a;
        rb = b;
      }
    }
    printf("%lld %lld\n", ra, rb);
  }
  return 0;
}

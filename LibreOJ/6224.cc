#include <cstdio>
#include <vector>
#include <map>

using int64 = long long;

int64 gcd(int64 a, int64 b) {
  return b ? gcd(b, a % b) : a;
}

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int64> a(n + 1), s(n + 1);
  std::map<int64, std::vector<int>> mp;
  s[0] = 0;
  mp[0].push_back(0);
  for (int i = 1; i <= n; ++i) {
    scanf("%lld", &a[i]);
    s[i] = a[i] ^ s[i - 1];
    mp[s[i]].push_back(i);
  }
  int64 m;
  scanf("%lld", &m);
  std::pair<int, int> ret(n + 1, n + 1);
  std::vector<std::pair<int64, int>> seg;
  for (int i = n; i >= 1; --i) {
    std::vector<std::pair<int64, int>> ts = {{a[i], i}};
    for (auto &&e: seg) {
      e.first = gcd(e.first, a[i]);
      if (e.first == ts.back().first) ts.back() = e;
      else ts.push_back(e);
    }
    seg.swap(ts);
    int L = i;
    for (auto &&e: seg) {
      if (m % e.first == 0) {
        int64 target = (m / e.first) ^ s[i - 1];
        auto it = mp.find(target);
        if (it != mp.end()) {
          auto &vs = it->second;
          auto x = std::lower_bound(vs.begin(), vs.end(), L);
          if (x != vs.end() && *x <= e.second) {
            ret = std::min(ret, {i, *x});
            break;
          }
        }
      }
      L = e.second + 1;
    }
  }
  if (ret.first == n + 1) puts("no solution");
  else printf("%d %d\n", ret.first, ret.second);
  return 0;
}

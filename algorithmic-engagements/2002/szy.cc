#include <cstdio>
#include <vector>
#include <algorithm>

using int64 = long long;

void solve() {
  int n;
  int64 S;
  scanf("%d", &n);
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
  scanf("%lld", &S);
  int x = n / 2, y = n - x;
  std::vector<std::pair<int64, int>> s(1 << x);
  for (int mask = 1; mask < (1 << x); ++mask) {
    int p = __builtin_ctz(mask);
    s[mask].first = s[mask ^ (1 << p)].first + a[p];
    s[mask].second = mask;
  }
  std::sort(s.begin(), s.end());
  for (int mask = 0; mask < (1 << y); ++mask) {
    int64 sum = 0;
    for (int i = 0; i < y; ++i) {
      if (mask >> i & 1) sum += a[i + x];
    }
    auto it = std::lower_bound(s.begin(), s.end(), std::make_pair(S - sum, -1));
    if (it != s.end() && it->first == S - sum) {
      for (int i = 0; i < x; ++i) {
        printf("%d", it->second >> i & 1);
      }
      for (int i = 0; i < y; ++i) {
        printf("%d", mask >> i & 1);
      }
      puts("");
      break;
    }
  }
}

int main() {
  int k;
  scanf("%d", &k);
  solve();
  return 0;
}

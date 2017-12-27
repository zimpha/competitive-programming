#include <cstdio>
#include <algorithm>
#include <vector>

using int64 = long long;

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int64 p, n;
    scanf("%lld%lld", &n, &p);
    std::vector<int64> a;
    do {
      a.emplace_back(n % p);
      n /= p;
    } while (n);
    int m = a.size();
    std::reverse(a.begin(), a.end());
    std::vector<int64> prod(m + 1), pw(m + 1);
    prod[m] = pw[0] = 1;
    for (int i = 1; i <= m; ++i) {
      pw[i] = pw[i - 1] * p;
    }
    for (int i = m - 1; i >= 0; --i) {
      prod[i] = prod[i + 1] * (a[i] + 1);
    }
    int64 ret = 0;
    for (int i = 0; i < m; ++i) {
      ret += a[i] * (pw[m - i - 1] - prod[i + 1]);
    }
    printf("%lld\n", ret);
  }
  return 0;
}

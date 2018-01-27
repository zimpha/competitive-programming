#include <cstdio>
#include <vector>
#include <map>

using int64 = long long;

int gcd(int a, int b) {
  return b ? gcd(b, a % b) : a;
}

int phi(int n) {
  int r = 0;
  for (int i = 1; i <= n; ++i) {
    r += gcd(i, n) == 1;
  }
  return r;
}

int dcnt(int n) {
  int r = 0;
  for (int i = 1; i <= n; ++i) {
    if (n % i == 0) ++r;
  }
  return r;
}

int main() {
  int64 n = 617985896071199040ll;
  /*int64 gn = 0;
  for (int64 i = 1; i * i <= n; ++i) if (n % i == 0) {
    gn += i;
    if (i * i != n) gn += n / i;
  }
  n = gn;*/
  const int64 mod = 1e9 + 7;
  std::map<int, int> mp;
  mp[1] = 0;
  int last = 1;
  int extra = 0, period = 0;
  std::vector<int> a = {1};
  for (int i = 1; ; ++i) {
    int now = (7ll * last % mod * last + 12 * last + 4) % mod;
    a.push_back(now);
    if (mp.count(now)) {
      extra = mp[now];
      period = i - mp[now];
      break;
    }
    mp[now] = i;
    last = now;
  }
  printf("%d %d\n", extra, period);
  int64 k = (n - extra - period) / period + 1;
  printf("%d\n", a[n - k * period]);
  return 0;
}

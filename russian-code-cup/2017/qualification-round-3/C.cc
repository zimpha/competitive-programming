#include <cstdio>
#include <algorithm>

using ll = long long;

ll pw[19];

int len(ll n) {
  int s = 0;
  while (n) ++s, n /= 10;
  return s;
}

ll solve(ll n) {
  if (n < 10) return n;
  int m = len(n);
  ll ret = 9;
  for (int i = 2; i < m; ++i) {
    ret += 9 * pw[i - 2];
  }
  int first = n / pw[m - 1];
  for (int i = m - 1; i >= 0; --i) {
    int o = n / pw[i] % 10;
    if (i) ret += o * pw[i - 1];
    else ret += o >= first;
    if (i == m - 1) ret -= pw[i - 1];
  }
  return ret;// + (first == n % 10);
}

int main() {
  pw[0] = 1;
  for (int i = 1; i < 19; ++i) {
    pw[i] = pw[i - 1] * 10;
  }
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    ll l, r;
    scanf("%lld%lld", &l, &r);
    printf("%lld\n", solve(r) - solve(l - 1));
  }
  return 0;
}

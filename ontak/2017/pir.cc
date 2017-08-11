#include <cstdio>
#include <vector>

using ll = long long;

ll gcd(ll a, ll b) {
  return b ? gcd(b, a % b) : a;
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  std::vector<ll> a(n), lcm(1 << n), sgn(1 << n);
  for (int i = 0; i < n; ++i) {
    scanf("%lld", &a[i]);
  }
  for (int mask = 0; mask < (1 << n); ++mask) {
    lcm[mask] = 1;
    sgn[mask] = -1;
    for (int i = 0; i < n; ++i) {
      if (mask >> i & 1) {
        ll g = gcd(lcm[mask], a[i]);
        lcm[mask] = lcm[mask] / g * a[i];
        sgn[mask] *= -1;
      }
    }
  }
  for (int i = 0; i < m; ++i) {
    ll q;
    scanf("%lld", &q);
    ll left = 1, right = 1000000000000000000ll;
    while (left < right) {
      ll mid = (left + right - 1) >> 1;
      ll cnt = 0;
      for (int mask = 1; mask < (1 << n); ++mask) {
        cnt += mid / lcm[mask] * sgn[mask];
      }
      if (cnt >= q) right = mid;
      else left = mid + 1;
    }
    printf("%lld\n", left);
  }
  return 0;
}

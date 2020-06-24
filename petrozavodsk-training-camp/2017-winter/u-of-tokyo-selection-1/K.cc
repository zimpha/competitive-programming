#include <cmath>
#include <cstdio>
#include <vector>

using ll = long long;

std::vector<int> mul(const std::vector<int> &a, const std::vector<int> &b) {
  std::vector<int> r(a.size());
  for (size_t i = 0; i < r.size(); ++i) {
    r[i] = b[a[i]];
  }
  return r;
}

std::vector<int> pow(std::vector<int> a, ll n) {
  std::vector<int> r(a.size());
  for (size_t i = 0; i < r.size(); ++i) {
    r[i] = i;
  }
  for (; n; n >>= 1) {
    if (n & 1) r = mul(r, a);
    a = mul(a, a);
  }
  return r;
}

std::vector<int> gcd(ll a, ll b, std::vector<int> x, std::vector<int> y) {
  if (b == 0) {
    return x;
  } else if (a == 0) {
    return y;
  } if (a >= b) {
    return gcd(a % b, b, x, mul(pow(x, a / b), y));
  } else {
    return gcd(a, b % a, mul(x, pow(y, b / a)), y);
  }
}

ll gcd(ll a, ll b) {
  return b ? gcd(b, a % b) : a;
}

int main() {
  ll a, b;
  scanf("%lld%lld", &a, &b);
  ll g = gcd(a, b);
  a /= g;
  b /= g;
  std::vector<int> x = {3, 0, 1, 2, 4, 5};
  std::vector<int> y = {4, 1, 5, 3, 2, 0};
  std::vector<int> p = gcd(a, b, x, y);
  std::vector<int> r(p.size());
  for (size_t i = 0; i < p.size(); ++i) {
    r[i] = i;
  }
  for (int i = 1; ; ++i) {
    r = mul(r, p);
    if (r == std::vector<int>{0, 1, 2, 3, 4, 5}) {
      printf("%.20f\n", hypot(a, b) * i);
      break;
    }
  }
  return 0;
}

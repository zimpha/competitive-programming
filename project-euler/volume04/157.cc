#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

LL dsum(int a, int b, int n) {
  int s2 = n, s5 = n; n = a + b;
  while (a % 2 == 0) --s2, a /= 2;
  while (a % 5 == 0) --s5, a /= 5;
  while (b % 2 == 0) --s2, b /= 2;
  while (b % 5 == 0) --s5, b /= 5;
  while (n % 2 == 0) ++s2, n /= 2;
  while (n % 5 == 0) ++s5, n /= 5;
  LL ret = (s2 + 1) * (s5 + 1);
  for (int i = 3; i * i <= n; ++i) if (n % i == 0) {
    int c = 0; while (n % i == 0) ++c, n /= i;
    ret *= (c + 1);
  }
  if (n > 1) ret *= 2;
  return ret;
}

LL solve(int n) {
  vector<int> fac;
  for (int i = 0; i <= n; ++i) {
    for (int j = 0, p = 1; j <= n; ++j, p *= 5) {
      fac.push_back((1 << i) * p);
    }
  }
  LL pw = 1; for (int i = 0; i < n; ++i) pw *= 10;
  LL ret = 0;
  for (auto a: fac) for (auto b: fac) {
    if (__gcd(a, b) != 1 || a > b) continue;
    if (1ll * a * b <= pw) ret += dsum(a, b, n);
  }
  return ret;
}

LL run(int n) {
  LL ret = 0;
  for (int i = 1; i <= n; ++i) {
    ret += solve(i);
  }
  return ret;
}

int main() {
  cout << solve(1) << endl;
  cout << run(9) << endl;
  return 0;
}

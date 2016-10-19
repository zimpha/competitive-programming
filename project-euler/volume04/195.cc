#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

LL run(int n) {
  LL ret = 0;
  for (LL u = 1; u <= n * 2; ++u) {
    for (LL v = 1; v < u; ++v) if (__gcd(u, v) == 1) {
      if ((u - v) % 3 == 0) continue;
      double r = u * v / 2.0 * sqrt(3);
      if (r <= n) ret += n / r;
      else break;
    }
  }
  for (LL p = 1; p * p <= n * 6; ++p) if (p % 3) {
    for (LL v = 1; ; ++v) if (__gcd(p, v) == 1) {
      double r = p * (p + v * 3) * sqrt(3) / 6;
      if (r <= n) ret += n / r;
      else break;
    }
  }
  return ret;
}

int main() {
  cout << run(100) << endl;
  cout << run(1000) << endl;
  cout << run(10000) << endl;
  cout << run(1053779) << endl;
  return 0;
}

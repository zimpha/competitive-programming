#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

int phi(int n) {
  int r = n;
  for (int i = 2; i * i <= n; ++i) {
    if (n % i == 0) {
      while (n % i == 0) n /= i;
      r = r / i * (i - 1);
    }
  }
  if (n > 1) r = r / n * (n - 1);
  return r;
}

LL pm(LL a, LL n, LL m) {
  LL r = 1;
  for (a %= m; n; n >>= 1) {
    if (n & 1) r = r * a % m;
    a = a * a % m;
  }
  return r;
}

LL run(int n, int m, int md) {
  if (md == 1) return 0;
  if (m == 1) return n % md;
  int ph = phi(md);
  return pm(n, run(n, m - 1, ph), md);
}

int main() {
  cout << run(3, 3, 100000000) << endl;
  cout << run(1777, 1855, 100000000) << endl;
  return 0;
}

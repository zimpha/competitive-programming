#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

LL pm(LL a, LL n, LL m) {
  LL r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % m;
    a = a * a % m;
  }
  return r;
}

LL run(int p, int q) {
  int n = p * q, phi = (p - 1) * (q - 1);
  vector<int> fac;
  for (int i = 1; i < phi; ++i) {
    if (phi % i == 0) fac.push_back(i);
  }
  vector<int> me(n, 0);
  for (int m = 2; m < n; ++m) {
    for (auto &e: fac) if (pm(m, e, n) == 1) {
      me[m] = e; break;
    }
  }
  vector<int> d(phi, 0), cnt(phi, 0);
  for (int m = 1; m < n; ++m) if (me[m]) d[me[m]]++;
  for (int m = 1; m < phi; ++m) {
    for (int e = m; e < phi; e += m) cnt[e + 1] += d[m];
  }
  int mx = n;
  for (int e = 2; e < phi; ++e) if (__gcd(phi, e) == 1) {
    mx = min(mx, cnt[e]);
  }
  LL ret = 0;
  for (int e = 2; e < phi; ++e) if (__gcd(phi, e) == 1) {
    if (mx == cnt[e]) ret += e;
  }
  return ret;
}

int main() {
  cout << run(1009, 3643) << endl;
  return 0;
}

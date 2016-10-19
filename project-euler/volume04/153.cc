#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

LL run(int n) {
  vector<int> fac(n + 1, 0);
  for (int i = 1; i <= n; ++i) {
    for (int j = i; j <= n; j += i) fac[j]+=i;
  }
  vector<int> cnt(n + 1, 0);
  for (int a = 1; a * a <= n; ++a) {
    for (int b = 1; a * a + b * b <= n; ++b) {
      if (__gcd(a, b) != 1) continue;
      cnt[a * a + b * b]+=a*2;
    }
  }
  LL ret = 0;
  for (int i = 1; i <= n; ++i) {
    for (int j = i; j <= n; j += i) {
      ret += cnt[i] * fac[j / i];
    }
  }
  for (int i = 1; i <= n; ++i) ret += fac[i];
  return ret;
}

int main() {
  cout << run(5) << endl;
  cout << run(100000) << endl;
  cout << run(100000000) << endl;
}

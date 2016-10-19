#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

int sol(int n) {
  int ret(0);
  for (int d = 2; d <= n; ++ d) {
    for (int i = 1; i < d; ++ i) if (__gcd(i, d) == 1) {
      ret += i * 3 > d && i * 2 < d;
    }
  }
  return ret;
}

int main() {
  cout << sol(8) << endl;
  cout << sol(12000) << endl;
  return 0;
}

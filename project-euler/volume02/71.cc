#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

int sol(int n) {
  int a(-1), b(-1);
  for (int d = 3; d <= n; ++ d) {
    int l = 1, r = d;
    while (l < r) {
      int m = (l + r + 1) >> 1;
      if (m * 7 < d * 3) l = m;
      else r = m - 1;
    }
    while (__gcd(l, d) != 1) -- l;
    if (a == -1) a = l, b = d;
    else if ((LL)a * d < (LL)b * l) a = l, b = d;
  }
  cout << a << " " << b << endl;
  return a;
}

int main() {
  cout << sol(8) << endl;
  cout << sol(1000000) << endl;
  return 0;
}

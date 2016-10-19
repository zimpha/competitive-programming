#include <bits/stdc++.h>
using namespace std;

int ok(int y, int n) {
  int d = n / y + y;
  if (d % 4) return 0;
  d /= 4;
  int x = y + d, z = y - d;
  return z > 0;
}

int sol(int n) {
  int ret = 0;
  for (int i = 1; i * i <= n; ++i) {
    if (n % i == 0) {
      ret += ok(i, n);
      if (i * i != n) ret += ok(n / i, n);
    }
  }
  return ret;
}

int run(int upp, int cnt) {
  int ret = 0;
  for (int i = 1; i < upp; ++i) {
    ret += sol(i) == cnt;
  }
  return ret;
}

int main() {
  cout << run(1000000, 10) << endl;
  return 0;
}

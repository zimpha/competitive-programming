#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

bool ok(int n) {
  if (n % 10 == 0) return 0;
  LL s = n, t = 0;
  while (n) {
    t = t * 10 + n % 10;
    n /= 10;
  }
  s += t;
  while (s) {
    if ((s % 10) % 2 == 0) return 0;
    s /= 10;
  }
  return 1;
}

int run(int n) {
  int ret = 0;
  for (int i = 1; i < n; ++i) {
    if (ok(i)) ++ret;
  }
  return ret;
}

int main() {
  cout << run(1e9) << endl;
  return 0;
}

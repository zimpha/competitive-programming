#include <bits/stdc++.h>
using namespace std;

int phi(int n) {
  if (__gcd(n, 10) != 1) return 0;
  for (int x = 1, k = 1; x; ) {
    x = (x * 10 + 1) % n; ++k;
    if (x == 0) return k;
  }
  return -1;
}

int run(int lim) {
  for (int n = 1000000; ; ++n) {
    if (phi(n) > lim) {
      return n;
    }
  }
  return -1;
}

int main() {
  cout << run(1000000) << endl;
  return 0;
}

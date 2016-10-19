#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

bool ok(LL n) {
  for (int i = 10; n; --i) {
    if (n % 10 != i % 10) return 0;
    n /= 100;
  }
  return true;
}

LL run() {
  for (int s = 101010101; s <= 138902662; ++s) {
    if (ok(s * 10ll * s * 10ll)) return s * 10ll;
  }
  return -1;
}

int main() {
  cout << run() << endl;
  return 0;
}

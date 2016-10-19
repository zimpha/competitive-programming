#include <bits/stdc++.h>
using namespace std;

int reverse(int n, int b) {
  int r(0);
  for (; n; n /= b) {
    r = r * b + n % b;
  }
  return r;
}

typedef long long LL;
LL sol(int n) {
  LL ret(0);
  for (int i = 1; i < n; ++ i) {
    if (reverse(i, 2) == i && reverse(i, 10) == i) {
      ret += i;
    }
  }
  return ret;
}

int main() {
  cout << sol(1000000) << endl;
  return 0;
}

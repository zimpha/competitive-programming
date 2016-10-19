#include <bits/stdc++.h>
using namespace std;

int sol(int n) {
  int ret(1);
  for (int i = 1; i <= n; ++ i) {
    ret = ret / __gcd(ret, i) * i;
  }
  return ret;
}

int main() {
  cout << sol(20) << endl;
  return 0;
}

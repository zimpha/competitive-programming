#include <bits/stdc++.h>
using namespace std;

int main() {
  int n = 10000000;
  int fac[10] = {1};
  for (int i = 1; i < 10; ++ i) {
    fac[i] = fac[i - 1] * i;
  }
  int ret(0);
  for (int i = 10; i < n; ++ i) {
    int tmp(0);
    for (int x = i; x; x /= 10) {
      tmp += fac[x % 10];
    }
    if (tmp == i) ret += i;
  }
  cout << ret << endl;
  return 0;
}

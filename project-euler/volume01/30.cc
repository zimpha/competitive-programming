#include <bits/stdc++.h>
using namespace std;

int sol() {
  int ret(0);
  for (int i = 2; i < 1e6; ++ i) {
    int s(0);
    for (int n = i; n; n /= 10) {
      int d(1);
      for (int _ = 0; _ < 5; ++ _) {
        d = d * (n % 10);
      }
      s += d;
    }
    if (s == i) ret += i;
  }
  return ret;
}

int main() {
  cout << sol() << endl;
  return 0;
}

#include <bits/stdc++.h>
using namespace std;

int sol() {
  int ret(-1);
  for (int i = 100; i <= 999; ++ i) {
    for (int j = i; j <= 999; ++ j) {
      int n = i * j, y = 0;
      for (int x = n; x; x /= 10) {
        y = y * 10 + x % 10;
      }
      if (n == y) ret = max(ret, i * j);
    }
  }
  return ret;
}

int main() {
  cout << sol() << endl;
  return 0;
}

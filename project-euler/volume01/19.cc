#include <bits/stdc++.h>
using namespace std;

int toWeekday(int y, int m, int d) {
  int tm = m >= 3 ? (m - 2) : (m + 10);
  int ty = m >= 3 ? y : y - 1;
  return (ty + ty / 4 - ty / 100 + ty / 400 + (int)(2.6 * tm - 0.2) + d) % 7;
}

int sol(int a, int b) {
  int ret(0);
  for (int y = a; y <= b; ++ y) {
    for (int m = 1; m <= 12; ++ m) {
      ret += !toWeekday(y, m, 1);
    }
  }
  return ret;
}

int main() {
  cout << sol(1901, 2000) << endl;
  return 0;
}

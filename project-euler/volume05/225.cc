#include <bits/stdc++.h>

bool ok(int m) {
  int t1 = 1, t2 = 1, t3 = 1;
  for (int i = 0; i < m * 100; ++i) {
    int x = (t1 + t2 + t3) % m;
    t1 = t2, t2 = t3, t3 = x;
    if (x == 0) return true;
  }
  return false;
}

int run(int n) {
  for (int s = 27; n; s += 2) {
    if (!ok(s)) --n;
    if (!n) return s;
  }
  return -1;
}

int main() {
  std::cout << run(124) << std::endl;
  return 0;
}

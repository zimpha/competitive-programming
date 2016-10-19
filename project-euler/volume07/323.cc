#include <bits/stdc++.h>

using LL = long long;

double run() {
  double ret = 0, p = 1;
  for (int i = 0; i < 100; ++i) {
    ret += 1 - pow(1 - p, 32);
    p *= 0.5;
  }
  return ret;
}

int main() {
  std::cout.precision(20);
  std::cout << run() << std::endl;
  return 0;
}


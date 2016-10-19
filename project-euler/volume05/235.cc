#include <bits/stdc++.h>

typedef long double flt;

flt run(int n, flt s) {
  flt left = 1.002, right = 1.003;
  for (int i = 0; i < 1000; ++i) {
    flt ret = 0, mid = (left + right) * 0.5;
    for (int k = n; k >= 1; --k) {
      ret = ret * mid + 900 - k * 3;
    }
    if (ret > s) left = mid;
    else right = mid;
  }
  return left;
}

int main() {
  std::cout.precision(13);
  std::cout << run(5000, -600000000000.0) << std::endl;
  return 0;
}

#include <bits/stdc++.h>

using LL = long long;

LL C[65][65];

LL f(int n) {
  LL ret = 1;
  for (int k = 1; k <= n / 2; ++k) {
    ret += C[n - k - 1][k - 1] * n / k;
  }
  return ret;
}

LL run() {
  for (int i = 0; i < 65; ++i) {
    C[i][0] = C[i][i] = 1;
    for (int j = 1; j < i; ++j) {
      C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
    }
  }
  return f(1) * f(2) * f(3) * f(6) * f(6) * f(46);
}

int main() {
  std::cout << run() << std::endl;
  return 0;
}

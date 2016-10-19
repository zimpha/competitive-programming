#include <bits/stdc++.h>

using LL = long long;

inline bool is_square(int n) {
  int x = sqrt(n);
  return x * x == n;
}

int run(int m) {
  int gcd[m + 1][m + 1];
  for (int i = 1; i <= m; ++i) {
    for (int j = 1; j <= m; ++j) {
      gcd[i][j] = std::__gcd(i, j);
    }
  }
  // pick: s = a + b / 2 - 1
  int ret = 0;
  for (int a = 1; a <= m; ++a) {
    for (int b = 1; b <= m; ++b) {
      for (int c = 1; c <= m; ++c) {
        for (int d = 1; d <= m; ++d) {
          int s = (b + d) * (a + c);
          int border = gcd[a][b] + gcd[a][d] + gcd[b][c] + gcd[c][d];
          int cnt = (s + 2 - border) / 2;
          ret += is_square(cnt);
        }
      }
    }
  }
  return ret;
}

int main() {
  std::cout << run(4) << std::endl;
  std::cout << run(100) << std::endl;
  return 0;
}


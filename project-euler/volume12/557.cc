#include <bits/stdc++.h>

using LL = long long;

//Menelaus' Theorem
//bc(2a+b+c+d)=a^2d
//S = a + b + c + d, a, d => (b, c) will faster
LL run(int n) {
  LL ret = 0;
  for (int b = 1; b < n; ++b) {
    for (int c = b; b + c < n; ++c) {
      for (int a = sqrt(b * c); a + b + c < n; ++a) {
        LL x = 1ll * b * c * (a * 2 + b + c);
        int y = a * a - b * c;
        if (y > 0 && x % y == 0) {
          LL d = x / y;
          if (a + b + c + d <= n) ret += a + b + c + d;
        }
      }
    }
  }
  return ret;
}

int main() {
  std::cout << run(20) << std::endl;
  std::cout << run(10000) << std::endl;
  return 0;
}


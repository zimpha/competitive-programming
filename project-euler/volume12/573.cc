#include <bits/stdc++.h>

double run(int n) {
  double res = 1.0, now = 1.0;
  for (int i = 2; i <= n; i++) {
    now = now * (n - i + 1) / n;
    res += now;
  }
  return res;
}

int main() {
  std::cout.precision(10);
  std::cout << run(3) << std::endl;
  std::cout << run(4) << std::endl;
  std::cout << run(5) << std::endl;
  std::cout << run(10) << std::endl;
  std::cout << run(1000000) << std::endl;
  return 0;
}

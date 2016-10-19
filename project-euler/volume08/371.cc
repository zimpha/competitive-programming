#include <bits/stdc++.h>

double run(int n) {
  double E0 = 0, E1 = 0;
  int t = n / 2 - 1;
  for (int i = t; i >= 0; --i) {
    E1 = (2 * (t - i) * E1 + n) / (n - 1 - i);
    E0 = (2 * (t - i) * E0 + E1 + n) / (n - 1 - i);
  }
  return E0;
}

int main() {
  std::cout.precision(20);
  std::cout << run(1000) << std::endl;
  return 0;
}

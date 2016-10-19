#include <bits/stdc++.h>

int f(int n) {
  if (n == 1 || n == 3) return n;
  if (n % 2 == 0) return f(n / 2);
  if (n % 4 == 1) return 2 * f(n / 4 * 2 + 1) - f(n / 4);
  if (n % 4 == 3) return 3 * f(n / 4 * 2 + 1) - 2 * f(n / 4);
  return -1;
}

int main() {
  for (int i = 1; i <= 100; ++i) {
    std::cout << f(i) << std::endl;
  }
  return 0;
}

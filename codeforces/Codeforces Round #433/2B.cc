#include <iostream>

int main() {
  int n, k;
  std::cin >> n >> k;
  if (k == 0 || k == n) std::cout << "0 0" << std::endl;
  else {
    std::cout << "1 ";
    int all = (n - 1) / 3 + 1;
    if (k <= all) std::cout << std::min(k * 2, n - k) << std::endl;
    else std::cout << (n - all) - (k - all) << std::endl;
  }
  return 0;
}
#include <bits/stdc++.h>

int main() {
  int ret = 0;
  for (unsigned int n = 1 << 30; n; --n) {
    ret += (n ^ (n << 1) ^ (n * 3)) == 0;
  }
  std::cout << ret << std::endl;
  return 0;
}

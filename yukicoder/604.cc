#include <iostream>

using int64 = long long;
using int128 = __int128_t;

int main() {
  int64 A, B, C;
  std::cin >> A >> B >> C;
  int64 l = 1, r = C;
  while (l < r) {
    int64 m = (l + r - 1) >> 1;
    int64 k = m / A;
    int128 u = m - k + (int128)k * B;
    if (u >= C) r = m;
    else l = m + 1;
  }
  std::cout << l << std::endl;
  return 0;
}

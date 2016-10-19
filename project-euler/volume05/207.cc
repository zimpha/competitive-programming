#include <bits/stdc++.h>

long long run(int a, int b) {
  int s = 0;
  for (int x = 1; ; ++x) {
    if (x != 1 && __builtin_popcount(x) == 1) ++s;
    if (s && 1ll * s * b < 1ll * a * x) {
      return 1ll * x * (x + 1);
    }
  }
  return -1;
}

int main() {
  std::cout << run(1, 12345) << std::endl;
  return 0;
}

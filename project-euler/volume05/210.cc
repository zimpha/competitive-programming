#include <bits/stdc++.h>

using LL = long long;

LL sum_ap(int n, int d) {// \sum i * d
  return 1ll * n * (n + 1) / 2 * d;
}

LL run(int r) {
  LL res = 0;
  // part I: (0 + 2 + .. + r/2) * 2 + (r / 2) * (r / 2) + (0 + 1 + ... + r/2-1)
  res += sum_ap(r / 4, 2) * 2 + 1ll * r * r / 4 + sum_ap(r / 2 - 1, 1);
  // part II: (r + 1) * (r / 2) + r * (r / 2)
  res += 1ll * (r + 1) * r / 2 + 1ll * r * r / 2;
  // part III: #[in circle]
  if (r % 8 == 0) {
    LL s = 1ll * r * r / 32;
    int border = r / 8 * sqrt(2);
    for (int x = -border; x <= border; ++x) {
      int y = sqrt(s - 1ll * x * x);
      while (1ll * x * x + 1ll * y * y <= s) ++y;
      while (y >= 0 && 1ll * x * x + 1ll * y * y >= s) --y;
      if (y >= 0) res += 2 * y + 1;
    }
  }
  // part IV: coline
  res -= r / 4 - 1 + r / 2 + r / 4;
  return res;
}

int main() {
  std::cout << run(4) << std::endl;
  std::cout << run(8) << std::endl;
  std::cout << run(1000000000) << std::endl;
  return 0;
}

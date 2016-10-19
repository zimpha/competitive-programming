#include <bits/stdc++.h>

using LL = long long;

// S(n, m) = 6m + 2n - 13, n < m
// S(n, n) = 8n - 11
LL run(int n) {
  std::vector<bool> mark(n, 1);
  for (int i = 2; i < n; ++i) if (mark[i]) {
    for (int j = i + i; j < n; j += i) mark[j] = 0;
  }
  LL ret = 0;
  for (int p = 2; p < n; ++p) if (mark[p]) {
    LL val = 1ll * p * p;
    if ((val - 5) % 8 == 0 && val >= 21) ++ret;
    val += 13; val /= 2;
    if (val % 3 == 0) ret += (val / 3 - 1) / 4 * 2;
    else if (val % 3 == 1) ret += ((val - 1) / 3 - 2) / 4 * 2;
    else {
      val = (val - 2) / 3 - 2;
      if (val > 0) ret += (val - 1) / 4 * 2;
    }
  }
  return ret + 2;
}

int main() {
  std::cout << run(100) << std::endl;
  std::cout << run(1000000) << std::endl;
  return 0;
}

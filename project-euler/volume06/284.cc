#include <bits/stdc++.h>

using LL = long long;

LL run(int n) {
  std::vector<int> a(n + 1);
  a[0] = 7;
  int carry = 3;
  for (int i = 1; i < n; ++i) {
    a[i] = carry;
    for (int j = 1; j < i; ++j) {
      a[i] += a[j] * a[i - j];
    }
    for (int d = 0; d < 14; ++d) {
      if (d == (a[i] + d * a[0] * 2) % 14) {
        carry = (a[i] + d * a[0] * 2) / 14;
        a[i] = d;
        break;
      }
    }
  }
  LL ret = 1, x = 0, y = 0;
  for (int i = 0; i < n; ++i) {
    int p = a[i], q = i ? 13 - a[i] : 15 - a[i];
    x += p, y += q;
    if (p) ret += x;
    if (q) ret += y;
  }
  return ret;
}

int main() {
  std::cout << run(1) << std::endl;
  std::cout << run(2) << std::endl;
  std::cout << run(9) << std::endl;
  std::cout << run(10000) << std::endl;
  return 0;
}

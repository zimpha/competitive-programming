#include <bits/stdc++.h>

bool solve(int x, int y, int a01, int a10) {
  if (x + y == 0) return false;
  if (a01 + a10 != x * y) return false;
  if (a01 > x * y || a10 > x * y) return false;
  int n = x + y;
  for (int i = 0; i < n; ++i) {
    if (x > 0 && y <= a01 && (x - 1) * y >= a01 - y && y * (x - 1) >= a10) {
      a01 -= y;
      --x;
      putchar('0');
    } else {
      a10 -= x;
      --y;
      putchar('1');
    }
  }
  puts("");
  return true;
}

void run() {
  int a00, a01, a10, a11;
  std::cin >> a00 >> a01 >> a10 >> a11;
  std::vector<int> x, y;
  for (int i = 0; i <= 1000000; ++i) {
    if (1ll * i * (i - 1) == a00 * 2) x.push_back(i);
    if (1ll * i * (i - 1) == a11 * 2) y.push_back(i);
  }
  for (auto &&a: x) for (auto &&b: y) {
    if (solve(a, b, a01, a10)) return;
  }
  puts("Impossible");
}

int main() {
  run();
  return 0;
}

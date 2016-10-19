#include <bits/stdc++.h>

int ds(long n) {
  int r = 0;
  while (n) r += 1, n /= 10;
  return r;
}

long pw(int n) {
  long r = 1;
  for (int i = 0; i < n; ++i) r *= 10;
  return r;
}

long solve(long l, long r, long x) {
  long ret = r - l, y = (x + (l + x-  1) / x) / 2 - 1;
  long b = ((2 * y + 1) - x) * x;
  while (l < r) {
    b += x * 2;
    if (b >= r) b = r - 1;
    if (++y != x) ret += solve(l, b + 1, y);
    l = b + 1;
  }
  return ret;
}

double run(long l, long r) {
  long d = ds(l), x0;
  if (d & 1) x0 = 2 * pw((d - 1) / 2);
  else x0 = 7 * pw(d / 2 - 1);
  return 1.0 * solve(l, r, x0) / (r - l);
}

int main() {
  std::cout.precision(20);
  std::cout << run(10000, 100000) << std::endl;
  std::cout << run(10000000000000ll, 100000000000000ll) << std::endl;
  return 0;
}

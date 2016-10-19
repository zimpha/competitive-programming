#include <bits/stdc++.h>

long mod_inv(long a, long m) {
  if (a > m) return mod_inv(a % m, m);
  if (a == 1) return 1;
  return m - m / a * mod_inv(m % a, m) % m;
}

long run(long n) {
  std::vector<bool> mark(n, 1);
  mark[0] = mark[1] = 0;
  for (int i = 2; i < n; ++i) if (mark[i]) {
    for (int j = i + i; j < n; j += i) mark[j] = 0;
  }
  long ret = 0;
  for (int i = 2; i < n; ++i) if (mark[i]) {
    if (i == 2 || i == 5) continue;
    ret += mod_inv(10, i);
  }
  return ret;
}

int main() {
  std::cout << run(1000) << std::endl;
  std::cout << run(10000000) << std::endl;
  return 0;
}

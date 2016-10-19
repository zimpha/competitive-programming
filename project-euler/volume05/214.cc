#include <bits/stdc++.h>

using LL = long long;

LL run(int n, int len) {
  std::vector<int> phi(n + 1, 0), pl;
  for (int i = 2; i <= n; ++i) {
    if (!phi[i]) phi[i] = i - 1, pl.push_back(i);
    for (size_t j = 0; j < pl.size() && i * pl[j] <= n; ++j) {
      int p = pl[j];
      phi[i * p] = phi[i] * (p - !!(i % p));
      if (i % p == 0) break;
    }
  }
  LL ret = 0;
  for (int i = 2; i <= n; ++i) {
    if (phi[i] != i - 1) continue;
    int chain = 1;
    for (int m = i; m != 1; m = phi[m]) {
      ++chain;
      if (chain > len) break;
    }
    if (chain == len) ret += i;
  }
  return ret;
}

int main() {
  std::cout << run(18, 4) << std::endl;
  std::cout << run(40000000, 25) << std::endl;
  return 0;
}

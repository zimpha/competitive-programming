#include <bits/stdc++.h>

using LL = long long;

const int M = 1e9 + 9;

LL pm(LL a, LL n) {
  LL r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % M;
    a = a * a % M;
  }
  return r;
}

LL run(int n) {
  std::vector<int> p;
  std::vector<bool> mark(n + 1);
  for (int i = 2; i <= n; ++i) {
    if (!mark[i]) p.push_back(i);
    for (size_t j = 0; j < p.size() && p[j] * i <= n; ++j) {
      mark[i * p[j]] = 1;
      if (i % p[j] == 0) break;
    }
  }
  LL ret = 1;
  for (auto &&x : p) {
    int cnt = 0;
    for (LL y = x; y <= n; y *= x) cnt += n / y;
    ret = ret * (1 + pm(x, cnt * 2)) % M;
  }
  return ret;
}

int main() {
  std::cout << run(4) << std::endl;
  std::cout << run(100000000) << std::endl;
  return 0;
}


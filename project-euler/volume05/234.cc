#include <bits/stdc++.h>

using LL = long long;

LL sum(LL n, LL p1, LL p2) {
  LL a = n / p1, b = n / p2, c = n / (p1 * p2);
  return (1 + a) * a / 2 * p1 + (1 + b) * b / 2 * p2 - (1 + c) * c * p1 * p2;
}

LL run(LL n) {
  int m = sqrt(n) * 2;
  std::vector<int> p, mark(m, 0);
  for (int i = 2; i < m; ++i) if (!mark[i]) {
    p.push_back(i);
    for (int j = i; j < m; j += i) mark[j] = 1;
  }
  LL ret = 0;
  for (size_t i = 1; i < p.size(); ++i) {
    int lps = p[i - 1], ups = p[i];
    ret += sum(std::min(1ll * ups * ups - 1, n), lps, ups);
    ret -= sum(std::min(1ll * lps * lps, n), lps, ups);
  }
  return ret;
}

int main() {
  assert(run(15) == 30);
  assert(run(1000) == 34825);
  std::cout << run(999966663333) << std::endl;
  return 0;
}

#include <bits/stdc++.h>

using LL = long long;

LL dfs(int d, LL now, int sgn, std::vector<int> &p) {
  if (now == 0) return 0;
  if (d == p.size()) return now * sgn;
  LL ret = dfs(d + 1, now, sgn, p);
  return ret + dfs(d + 1, now / p[d], -sgn, p);
}

LL solve1(LL n, std::vector<int> &p) {
  return n + dfs(0, n, -1, p);
}

LL exlude(LL n, std::vector<int> &p, int a, int b = 1, int c = 1) {
  std::vector<int> q;
  for (auto &&x: p) {
    if (x != a && x != b && x != c) q.push_back(x);
  }
  n /= a * b * c;
  return dfs(0, n, 1, q);
}

LL run(LL n) {
  --n;
  std::vector<int> p = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};
  LL ret = solve1(n, p);
  for (size_t i = 0; i < p.size(); ++i) {
    ret -= exlude(n, p, p[i]);
    for (size_t j = i + 1; j < p.size(); ++j) {
      ret -= exlude(n, p, p[i], p[j]);
      for (size_t k = j + 1; k < p.size(); ++k) {
        ret -= exlude(n, p, p[i], p[j], p[k]);
      }
    }
  }
  return ret;
}

int main() {
  std::cout << run(1000) << std::endl;
  std::cout << run(10000000000000000ll) << std::endl;
  return 0;
}


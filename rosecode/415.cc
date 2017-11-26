#include <cstdio>
#include <cassert>
#include <vector>
#include <set>
#include <iostream>

using int64 = long long;

std::vector<int> divisor(int n) {
  std::vector<int> d;
  for (int i = 1; i <= n; ++i) {
    if (n % i == 0) d.push_back(i);
  }
  return d;
}

void C(int D) {
  printf("%d: ", D);
  std::vector<std::vector<int>> all;
  for (int x = 0; x <= D; ++x) {
    auto d = divisor(x * x + D);
    for (auto &&y: d) all.push_back({x, y, (x * x + D) / y});
  }
  std::set<std::vector<int>> ban;
  for (auto &&e: all) {
    ban.insert({e[0] + e[1], e[1], 2 * e[0] + e[1] + e[2]});
    ban.insert({e[0] + e[2], 2 * e[0] + e[1] + e[2], e[2]});
  }
  int cnt = 0;
  for (auto &&e: all) if (!ban.count(e) && e[0]) {
    ++cnt;
  }
  printf("%d\n", cnt);
}

int64 S(int n) {
  int64 ret = 0;
  for (int i = 1; i <= n; ++i) ret += n / i;
  for (int x = 1; x <= n; ++x) {
    for (int y = 1, u = n / x; y <= u; ++y) {
      // xy + yz + zx <= n
      // z <= (n - xy)/(x+y)
      ret += (n - x * y) / (x + y);
    }
  }
  return ret;
}

int main() {
  std::cout << S(10) << std::endl;
  std::cout << S(100) << std::endl;
  std::cout << S(30000000) << std::endl;
  return 0;
}

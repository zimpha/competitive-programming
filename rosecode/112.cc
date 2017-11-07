#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

// http://oeis.org/A071053
int solve(int n) {
  std::vector<int> runs;
  int cnt = 0;
  while (n) {
    if (n & 1) ++cnt;
    else {
      if (cnt) runs.push_back(cnt);
      cnt = 0;
    }
    n /= 2;
  }
  if (cnt) runs.push_back(cnt);
  n = *std::max_element(runs.begin(), runs.end()) + 2;
  std::vector<int> a(n + 1);
  a[0] = 0, a[1] = 1;
  for (int i = 2; i <= n; ++i) {
    a[i] = a[i - 1] + 2 * a[i - 2];
  }
  int ret = 1;
  for (auto &&x: runs) ret *= a[x + 2];
  return ret;
}

int main() {
  std::cout << solve(7) << std::endl;
  std::cout << solve(6700417) << std::endl;
  return 0;
}

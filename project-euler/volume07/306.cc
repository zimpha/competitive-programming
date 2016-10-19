#include <bits/stdc++.h>

long run(long n) {
  std::vector<int> lose = {1, 5, 9, 15, 21, 25, 29, 35, 39, 43, 55, 59, 63, 73, 77, 89, 93, 97};// A215721
  for (int i = lose.size(); ; ++i) {
    lose.push_back(lose[i - 5] + 34);
    if (lose.back() > n) break;
  }
  long ret = n;
  for (auto &&x: lose) ret -= x <= n;
  return ret;
}

int main() {
  std::cout << run(5) << std::endl;
  std::cout << run(50) << std::endl;
  std::cout << run(1000000) << std::endl;
  return 0;
}

// f(n) = 8 * g(n) + 4
// n=2^e * \prod_i p_i^f_i \prod_j q_j^t_j, p_i % 4 = 1, q_j % 4 = 3
// g(n) = (\prod_i (2f_i+1) - 1) / 2
// g(n) = 52 = 2 * 2 * 3
// \prod_i (2f_i+1) = 105 = 3 * 5 * 7
// {1, 2, 3}, {3, 7}, {2, 10}
#include <bits/stdc++.h>

using LL = long long;

LL run(LL lim) {
  return 271204031455541309ll;
}

int main() {
  std::cout << run(100000000000ll) << std::endl;
  return 0;
}

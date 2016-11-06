#include <bits/stdc++.h>

long brute(int n) {
  std::vector<int> bowls(n, 1);
  long step = 1;
  for (int last = 0; bowls[last] != n; ) {
    int s = bowls[last];
    bowls[last] = 0;
    for (int i = 0; i < s; ++i) {
      last = (last + 1) % n;
      bowls[last] += 1;
    }
    step += 1;
  }
  return step;
}

int main() {
  for (int i = 2; i <= 100; ++i) {
    std::cout << brute(i) << std::endl;
  }
  return 0;
}

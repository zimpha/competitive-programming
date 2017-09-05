#include <bits/stdc++.h>

void run() {
  int n;
  std::cin >> n;
  std::vector<int> x(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> x[i];
  }
  std::sort(x.begin(), x.end());
  std::cout << x[(n - 1) / 2] << std::endl;
}

int main() {
  run();
  return 0;
}

#include <bits/stdc++.h>

void run() {
  int n;
  std::cin >> n;
  std::vector<int> x(n);
  for (int i = 0; i < n; ++i) std::cin >> x[i];
  std::sort(x.begin(), x.end());
  int q;
  std::cin >> q;
  for (int i = 0; i < q; ++i) {
    int m;
    std::cin >> m;
    std::cout << std::upper_bound(x.begin(), x.end(), m) - x.begin() << std::endl;
  }
}

int main() {
  run();
  return 0;
}

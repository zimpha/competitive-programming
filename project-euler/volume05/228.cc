#include <bits/stdc++.h>

int run(int l, int r) {
  std::set<std::pair<int, int>> S;
  for (int n = l; n <= r; ++n) {
    for (int i = 0; i < n; ++i) {
      int a = i * 360, b = n;
      int g = std::__gcd(a, b);
      S.insert({a / g, b / g});
    }
  }
  return S.size();
}

int main() {
  assert(run(3, 4) == 6);
  std::cout << run(1864, 1909) << std::endl;
  return 0;
}

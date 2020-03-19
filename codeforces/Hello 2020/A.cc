#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>

int main() {
  int n, m;
  std::cin >> n >> m;
  std::vector<std::string> s(n), t(m);
  for (int i = 0; i < n; ++i) std::cin >> s[i];
  for (int i = 0; i < m; ++i) std::cin >> t[i];
  int q;
  std::cin >> q;
  for (int i = 0; i < q; ++i) {
    int y;
    std::cin >> y;
    std::cout << s[(y - 1) % n] << t[(y - 1) % m] << std::endl;
  }
  return 0;
}

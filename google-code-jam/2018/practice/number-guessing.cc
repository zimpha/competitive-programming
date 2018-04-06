#include <iostream>
#include <string>

int main() {
  int T;
  std::cin >> T;
  for (int cas = 1; cas <= T; ++cas) {
    int a, b, n;
    std::cin >> a >> b >> n;
    ++a;
    for (int it = 0; it < n; ++it) {
      int p = (a + b) >> 1;
      std::cout << p << std::endl;
      std::string res;
      std::cin >> res;
      if (res == "TOO_BIG") b = p - 1;
      else if (res == "TOO_SMALL") a = p + 1;
      else break;
    }
  }
  return 0;
}

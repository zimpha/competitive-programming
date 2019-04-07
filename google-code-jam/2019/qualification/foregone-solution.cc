#include <cstdio>
#include <iostream>
#include <string>

int main() {
  int T;
  std::cin >> T;
  for (int cas = 1; cas <= T; ++cas) {
    std::string n;
    std::cin >> n;
    std::string a, b;
    bool zero_a = true, zero_b = true;
    for (size_t i = 0; i < n.size(); ++i) {
      if (n[i] == '1') {
        if (zero_a) {
          a.push_back('1');
          b.push_back('0');
          zero_a = false;
        } else if (zero_b) {
          a.push_back('0');
          b.push_back('1');
          zero_b = false;
        } else {
          a.push_back('1');
          b.push_back('0');
        }
      } else if (n[i] == '5') {
        a.push_back('2');
        b.push_back('3');
        zero_a = zero_b = false;
      } else if (n[i] == '0') {
        a.push_back('0');
        b.push_back('0');
      } else {
        a.push_back('1');
        b.push_back(n[i] - 1);
        zero_a = zero_b = false;
      }
    }
    size_t ia = 0, ib = 0;
    while (a[ia] == '0' && ia < a.size()) ++ia;
    while (b[ib] == '0' && ib < b.size()) ++ib;
    if (ib == b.size()) {
      a = "5";
      b = "5";
      for (size_t i = 2; i < n.size(); ++i) {
        a.push_back('0');
        b.push_back('0');
      }
      ia = ib = 0;
    }
    printf("Case #%d: %s %s\n", cas, a.substr(ia).c_str(), b.substr(ib).c_str());
  }
  return 0;
}

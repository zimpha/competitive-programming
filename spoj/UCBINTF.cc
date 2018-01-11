#include <iostream>
#include <string>

int main() {
  std::string s;
  std::cin >> s;
  int Amol = 0, Cdur = 0;
  for (size_t i = 0; i < s.size(); ++i) {
    if (i == 0 || s[i - 1] == '|') {
      if (s[i] == 'A' || s[i] == 'D' || s[i] == 'E') {
        Amol++;
      }
      if (s[i] == 'C' || s[i] == 'F' || s[i] == 'G') {
        Cdur++;
      }
    }
  }
  if (Amol == Cdur) {
    Amol += (s[s.size() - 1] == 'A');
    Cdur += (s[s.size() - 1] == 'C');
  }
  if (Amol == Cdur) {
    std::cout << "Ilegalan primjer!" << std::endl;
  } else {
    std::cout << (Amol > Cdur? "A-mol" : "C-dur") << std::endl;
  }
  return 0;
}

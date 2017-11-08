#include <iostream>
#include <string>
#include <vector>

int main() {
  std::string o, s;
  std::cin >> o >> s;
  std::vector<int> stack = {o[0] == 'B'};
  for (auto &&c: s) {
    if (stack.empty()) {
      puts("NO");
      return 0;
    }
    int top = stack.back();
    if (c == 'A') {
      if (top == 1) stack.pop_back();
      else stack.push_back(top ^ 1);
    } else {
      if (top == 0) stack.pop_back();
      else stack.push_back(top ^ 1);
    }
  }
  puts(stack.empty() ? "YES" : "NO");
  return 0;
}

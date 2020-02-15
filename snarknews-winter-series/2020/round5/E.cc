#include <cassert>
#include <cstdio>
#include <vector>
#include <iostream>

using int64 = long long;

const int mod = 998244353;

int main() {
  std::string s;
  std::getline(std::cin, s);
  std::getline(std::cin, s);
  std::vector<int64> stk = {0};
  for (size_t i = 0; i < s.size(); ++i) {
    if (s[i] == '(') {
      if (stk.size() & 1) stk.push_back(1);
      else stk.push_back(0);
    } else if (s[i] == ')') {
      int64 u = stk.back(); stk.pop_back();
      if (stk.size() & 1) stk.back() = (stk.back() + u) % mod;
      else stk.back() = (stk.back() * u) % mod;
    } else if (s[i] >= '0' && s[i] <= '9') {
      int64 u = 0;
      size_t j = i;
      for (; j < s.size() && '0' <= s[j] && s[j] <= '9'; ++j) {
        u = (u * 10 + s[j] - '0') % mod;
      }
      i = j - 1;
      if (stk.size() & 1) stk.back() = (stk.back() + u) % mod;
      else stk.back() = stk.back() * u % mod;
    }
  }
  assert(stk.size() == 1);
  printf("%lld\n", stk.back());
  return 0;
}

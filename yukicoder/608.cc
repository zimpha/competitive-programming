#include <cstdio>
#include <iostream>
#include <algorithm>

int solve(int p, std::string s) {
  int l = 0, n = s.size(), ret = 0;
  while (l < p && s[l] == '.') ++l;
  if (l != p) {
    for (int i = p - 1; i >= l; --i) {
      s[i] = '#' + '.' - s[i];
      ++ret;
    }
  }
  while (n > 1 && s[n - 1] == '.') --n;
  for (int r; ;) {
    for (r = l; r < n && s[l] == s[r]; ++r);
    if (r == n) {
      if (s[l] == '#') {
        if (r - l == 1) ret += 3;
        else ret += 2 + (r - l - 2) * 3;
      }
      break;
    } else {
      if (s[l] == '#') {
        ret += (r - l) * 3;
        l = r;
      } else {
        if (r - l == 2) ret += 1, s[l + 1] = '#', ++l;
        else if ((r - l) % 2 == 0) ret += 2 * (r - l), l = r;
        else {
          ret += 1 + (r - l - 1) * 2;
          s[r] = '.';
          l = r;
        }
      }
    }
  }
  return ret;
}

int main() {
  int n;
  std::string s;
  std::cin >> n >> s;
  int ret = solve(n - 1, s);
  std::reverse(s.begin(), s.end());
  ret = std::min(ret, solve(s.size() - n, s));
  std::cout << ret << std::endl;
  return 0;
}

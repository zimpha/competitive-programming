#include <cstdio>
#include <cstring>
#include <string>
#include <set>
#include <iostream>
#include <algorithm>

int lcs(const char *s, int n) {
  for (int i = 0, j = 1, k, ci, cj; ;) {
    for (k = 0; k < n; ++k) {
      ci = s[(i + k) % n];
      cj = s[(j + k) % n];
      if (ci != cj) break;
    }
    if (k == n) return std::min(i,j);
    if (ci > cj) i += k + 1,i += i == j;
    else j += k + 1, j += i==j;
  }
  return -1;
}

int main() {
  std::string x = "abcdefghijklmnopqrstuvwxyz";
  std::string y = "nopqrstuvwxyzabcdefghijklm";
  char go[256];
  for (int i = 0; i < 26; ++i) {
    go[(int)x[i]] = y[i];
  }
  int n;
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  std::cin >> n;
  std::set<std::string> ss;
  for (int i = 0; i < n; ++i) {
    std::string s;
    std::cin >> s;
    ss.insert(s);
  }
  int ret = 0;
  for (auto &s: ss) {
    std::string t = s;
    for (auto &c: t) c = go[(int)c];
    ret += ss.count(t);
  }
  printf("%d\n", ret);
  return 0;
}

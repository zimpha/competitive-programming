#include <cstdio>
#include <string>
#include <vector>

bool is_prefix(std::string s, std::string t) {
  for (size_t i = 0; i < t.size(); ++i) {
    if (s[i] != t[i]) return false;
  }
  return true;
}

bool is_suffix(std::string s, std::string t) {
  for (size_t i = 0; i < t.size(); ++i) {
    if (s[s.size() - 1 - i] != t[t.size() - 1 - i]) return false;
  }
  return true;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    std::vector<std::string> s(n);
    std::vector<std::string> suffix(n), prefix(n);
    int si = -1, pi = -1;
    for (int i = 0; i < n; ++i) {
      static char buf[1000];
      scanf("%s", buf);
      s[i] = buf;
      int p1 = -1, p2 = -1;
      for (size_t j = 0; j < s[i].size(); ++j) if (s[i][j] == '*') {
        if (p1 == -1) p1 = j;
        p2 = j;
      }
      prefix[i] = s[i].substr(0, p1);
      suffix[i] = s[i].substr(p2 + 1);
      if (si == -1 || suffix[i].size() > suffix[si].size()) si = i;
      if (pi == -1 || prefix[i].size() > prefix[pi].size()) pi = i;
    }
    bool valid = true;
    for (int i = 0; i < n; ++i) {
      valid &= is_prefix(prefix[pi], prefix[i]);
      valid &= is_suffix(suffix[si], suffix[i]);
    }
    if (!valid) printf("Case #%d: *\n", cas);
    else {
      std::string ret = prefix[pi];
      for (int i = 0; i < n; ++i) {
        for (auto &c: s[i]) if (c != '*') ret.push_back(c);
      }
      ret += suffix[si];
      printf("Case #%d: %s\n", cas, ret.c_str());
    }
  }
  return 0;
}

#include <bits/stdc++.h>

using LL = long long;

std::string run(int n, int k) {
  std::string s(n, ' ');
  for (int i = 0; i < n; ++i) s[i] = 'A' + i;
  std::vector<std::string> res;
  int mx = 0;
  do {
    std::string t = s;
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
      if (t[i] == 'A' + i) continue;
      for (int j = i + 1; j < n; ++j) {
        if (t[j] == 'A' + i) {
          if (j != n - 1) {
            std::reverse(t.begin() + j, t.end());
            ++cnt;
          }
          std::reverse(t.begin() + i, t.end());
          ++cnt;
          break;
        }
      }
    }
    if (cnt > mx) {
      res.clear();
      res.push_back(s);
      mx = cnt;
    } else if (cnt == mx && res.size() < k) {
      res.push_back(s);
    }
  } while (next_permutation(s.begin(), s.end()));
  return res[k - 1];
}

int main() {
  std::cout << run(6, 10) << std::endl;
  std::cout << run(11, 2011) << std::endl;
  return 0;
}


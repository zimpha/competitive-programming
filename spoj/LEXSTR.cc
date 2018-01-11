#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <iostream>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  int T;
  std::cin >> T;
  for (int cas = 1; cas <= T; ++cas) {
    std::string s;
    std::cin >> s;
    int n = s.size();
    std::vector<int> dsu(n);
    for (int i = 0; i < n; ++i) {
      dsu[i] = i;
    }
    std::function<int(int)> root = [&](int x) {
      if (x != dsu[x]) dsu[x] = root(dsu[x]);
      return dsu[x];
    };
    int m;
    std::cin >> m;
    for (int i = 0; i < m; ++i) {
      int x, y;
      std::cin >> x >> y;
      dsu[root(x)] = root(y);
    }
    std::vector<std::vector<int>> group(n);
    for (int i = 0; i < n; ++i) {
      group[root(i)].push_back(i);
    }
    for (int i = 0; i < n; ++i) {
      std::vector<char> t;
      for (auto &&x: group[i]) t.push_back(s[x]);
      std::sort(t.begin(), t.end());
      for (size_t j = 0; j < group[i].size(); ++j) {
        s[group[i][j]] = t[j];
      }
    }
    std::cout << s << std::endl;
  }
  return 0;
}

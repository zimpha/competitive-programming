#include <iostream>
#include <string>
#include <vector>

int ret[26][26][26];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  int n, m;
  std::cin >> n >> m;
  std::vector<std::string> s(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> s[i];
  }
  for (int i = n - 1; i >= 0; --i) {
    std::vector<int> last(26, -1), first(26, -1);
    for (size_t j = 0; j < s[i].size(); ++j) {
      last[s[i][j] - 'a'] = j;
    }
    for (int j = s[i].size() - 1; j >= 0; --j) {
      first[s[i][j] - 'a'] = j;
    }
    for (size_t j = 0; j < s[i].size(); ++j) {
      int c = s[i][j] - 'a';
      for (int a = 0; a < 26; ++a) if (first[a] != -1 && first[a] < j) {
        for (int b = 0; b < 26; ++b) if (last[b] != -1 && last[b] > j) {
          ret[a][c][b] = i + 1;
        }
      }
    }
  }
  for (int i = 0; i < m; ++i) {
    std::string q;
    std::cin >> q;
    int a = q[0] - 'A', b = q[1] - 'A', c = q[2] - 'A';
    if (ret[a][b][c]) {
      puts(s[ret[a][b][c] - 1].c_str());
    } else {
      puts("No valid word");
    }
  }
  return 0;
}

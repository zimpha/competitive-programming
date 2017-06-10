#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

int calc(std::vector<int> tile) {
  int ret = 0, sum = 0;
  for (int i = 0; i < tile.size(); ++i) {
    sum += tile[i];
    int tmp = 0;
    for (int j = i + 1; j < tile.size(); ++j) {
      tmp += tile[j];
      if (tmp <= sum) ret = std::max(ret, j - i);
    }
  }
  return ret;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, m;
    scanf("%d%d", &n, &m);
    std::vector<std::string> tile(n);
    for (int i = 0; i < n; ++i) {
      std::cin >> tile[i];
    }
    int ret = 0;
    for (int i = 0; i < n; ++i) {
      std::vector<int> v;
      for (int j = 0; j < m; ++j) {
        v.push_back(tile[i][j] - '0');
      }
      ret = std::max(ret, calc(v));
      std::reverse(v.begin(), v.end());
      ret = std::max(ret, calc(v));
    }
    for (int j = 0; j < m; ++j) {
      std::vector<int> v;
      for (int i = 0; i < n; ++i) {
        v.push_back(tile[i][j] - '0');
      }
      ret = std::max(ret, calc(v));
      std::reverse(v.begin(), v.end());
      ret = std::max(ret, calc(v));
    }
    printf("Case #%d: %d\n", cas, ret);
  }
  return 0;
}

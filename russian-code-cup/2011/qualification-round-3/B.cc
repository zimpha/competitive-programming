#include <cstdio>
#include <vector>
#include <string>
#include <iostream>

int main() {
  int w, h;
  scanf("%d%d", &w, &h);
  std::vector<std::string> grid(h);
  for (int i = 0; i < h; ++i) {
    std::cin >> grid[i];
  }
  const int dx[] = {-1, 0};
  const int dy[] = {0, -1};
  int ret = 0;
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      for (int k = 0; k < 2; ++k) {
        int x = i + dx[k], y = j + dy[k];
        if (x >= 0 && y >= 0) ret += grid[i][j] != grid[x][y];
      }
    }
  }
  printf("%d\n", ret);
  return 0;
}

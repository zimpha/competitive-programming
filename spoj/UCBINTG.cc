#include <iostream>
#include <algorithm>

char mapa[12][12];
char novamapa[12][12];
int u[] = {0, 0, 1, -1};
int v[] = {1, -1, 0, 0};

int main() {
  int r, s;
  std::cin >> r >> s;
  int mini = 100, maxi = 0, minj = 100, maxj = 0;
  for (int i = 0; i < r; ++i) {
    std::cin >> mapa[i];
  }
  for (int i = 0; i < r; ++i) {
    for (int j = 0; j < s; ++j) {
      int more = 0;
      for (int k = 0; k < 4; ++k) {
        int x = i + u[k];
        int y = j + v[k];
        if (x < 0 || y < 0 || x >= r || y >= s || mapa[x][y] == '.')
          more++;
      }
      if (more >= 3)
        novamapa[i][j] = '.';
      else
        novamapa[i][j] = mapa[i][j];
      if (novamapa[i][j] == 'X') {
        mini = std::min(mini, i);
        maxi = std::max(maxi, i);
        minj = std::min(minj, j);
        maxj = std::max(maxj, j);
      }
    }
  }
  for (int i = mini; i <= maxi; ++i) {
    for (int j = minj; j <= maxj; ++j) {
      std::cout << novamapa[i][j];
    }
    std::cout << std::endl;
  }
  return 0;
}

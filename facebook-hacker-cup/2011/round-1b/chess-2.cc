#include <cstdio>
#include <cstring>
#include <algorithm>

const int N = 16;
char chess[N][N];
bool mark[N][N];


void king(int x, int y) {
  for (int i = 0; i < 16; ++i) {
    for (int j = 0; j < 16; ++j) {
      if (i == x && j == y) continue;
      if (chess[i][j] && std::max(std::abs(i - x), std::abs(j - y)) == 1) {
        mark[i][j] = 1;
      }
    }
  }
}

void rook(int x, int y) {
  for (int i = x + 1; i < 16; ++i) if (chess[i][y]) {
    mark[i][y] = true;
    break;
  }
  for (int i = x - 1; i >= 0; --i) if (chess[i][y]) {
    mark[i][y] = true;
    break;
  }
  for (int i = y + 1; i < 16; ++i) if (chess[x][i]) {
    mark[x][i] = true;
    break;
  }
  for (int i = y - 1; i >= 0; --i) if (chess[x][i]) {
    mark[x][i] = true;
    break;
  }
}

void bishop(int x, int y) {
  for (int i = 1; x + i < 16 && y + i < 16; ++i) if (chess[x + i][y + i]) {
    mark[x + i][y + i] = true;
    break;
  }
  for (int i = 1; x + i < 16 && y - i >= 0; ++i) if (chess[x + i][y - i]) {
    mark[x + i][y - i] = true;
    break;
  }
  for (int i = 1; x - i >= 0 && y + i < 16; ++i) if (chess[x - i][y + i]) {
    mark[x - i][y + i] = true;
    break;
  }
  for (int i = 1; x - i >= 0 && y - i >= 0; ++i) if (chess[x - i][y - i]) {
    mark[x - i][y - i] = true;
    break;
  }
}

void queen(int x, int y) {
  bishop(x, y);
  rook(x, y);
}

void knight(int x, int y) {
  for (int i = 0; i < 16; ++i) {
    for (int j = 0; j < 16; ++j) {
      int a = std::abs(i - x), b = std::abs(j - y);
      if (a > b) std::swap(a, b);
      if (a == 1 && b == 2 && chess[i][j]) {
        mark[i][j] = true;
      }
    }
  }
}

void nightrider(int x, int y) {
  for (int i = 1; x + i < 16 && y + i * 2 < 16; ++i) if (chess[x + i][y + i * 2]) {
    mark[x + i][y + i * 2] = true;
    break;
  }
  for (int i = 1; x + i < 16 && y - i * 2 >= 0; ++i) if (chess[x + i][y - i * 2]) {
    mark[x + i][y - i * 2] = true;
    break;
  }
  for (int i = 1; x - i >= 0 && y + i * 2 < 16; ++i) if (chess[x - i][y + i * 2]) {
    mark[x - i][y + i * 2] = true;
    break;
  }
  for (int i = 1; x - i >= 0 && y - i * 2 >=0; ++i) if (chess[x - i][y - i * 2]) {
    mark[x - i][y - i * 2] = true;
    break;
  }
  for (int i = 1; x + i * 2 < 16 && y + i < 16; ++i) if (chess[x + i * 2][y + i]) {
    mark[x + i * 2][y + i] = true;
    break;
  }
  for (int i = 1; x + i * 2 < 16 && y - i >= 0; ++i) if (chess[x + i * 2][y - i]) {
    mark[x + i * 2][y - i] = true;
    break;
  }
  for (int i = 1; x - i * 2 >= 0 && y + i < 16; ++i) if (chess[x - i * 2][y + i]) {
    mark[x - i * 2][y + i] = true;
    break;
  }
  for (int i = 1; x - i * 2 >= 0 && y - i >= 0; ++i) if (chess[x - i * 2][y - i]) {
    mark[x - i * 2][y - i] = true;
    break;
  }
}

void archbishop(int x, int y) {
  knight(x, y);
  bishop(x, y);
}

void kraken(int x, int y) {
  for (int i = 0; i < 16; ++i) {
    for (int j = 0; j < 16; ++j) {
      if (i == x && j == y) continue;
      if (chess[i][j]) {
        mark[i][j] = true;
      }
    }
  }
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    memset(chess, 0, sizeof(chess));
    memset(mark, 0, sizeof(mark));
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
      char s[10];
      int r, f;
      scanf("%s%d%d", s, &r, &f);
      chess[r - 1][f - 1] = s[0];
    }
    for (int i = 0; i < 16; ++i) {
      for (int j = 0; j < 16; ++j) {
        if (chess[i][j] == 'K') king(i, j);
        if (chess[i][j] == 'Q') queen(i, j);
        if (chess[i][j] == 'R') rook(i, j);
        if (chess[i][j] == 'B') bishop(i, j);
        if (chess[i][j] == 'N') knight(i, j);
        if (chess[i][j] == 'S') nightrider(i, j);
        if (chess[i][j] == 'A') archbishop(i, j);
        if (chess[i][j] == 'E') kraken(i, j);
      }
    }
    int ret = 0;
    for (int i = 0; i < 16; ++i) {
      for (int j = 0; j < 16; ++j) {
        ret += mark[i][j];
      }
    }
    printf("Case #%d: %d\n", cas, ret);
  }
  return 0;
}

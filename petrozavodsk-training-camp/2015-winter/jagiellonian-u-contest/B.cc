#include <cstdio>
#include <algorithm>

char s[10][10];

void U(int y) {
  printf("%d U 1\n", y + 1);
  s[6][y] = s[0][y];
  for (int i = 0; i < 6; ++i) s[i][y] = s[i + 1][y];
}

void D(int y) {
  printf("%d D 1\n", y + 1);
  for (int i = 5; i >= 0; --i) s[i + 1][y] = s[i][y];
  s[0][y] = s[6][y];
}

void L(int x) {
  printf("%d L 1\n", x + 1);
  s[x][6] = s[x][0];
  for (int i = 0; i < 6; ++i) s[x][i] = s[x][i + 1];
}

void R(int x) {
  printf("%d R 1\n", x + 1);
  for (int i = 5; i >= 0; --i) s[x][i + 1] = s[x][i];
  s[x][0] = s[x][6];
}

void swapr(int i, int j) { // (i,j) (i,j+1)
  U(j); L(i); U(j); R(i);
  U(j); L(i); U(j); R(i);
  U(j); L(i); U(j); R(i);
  U(j);
}

void swapc(int i, int j) { // (i,j) (i+1,j)
  L(i); U(j); L(i); D(j);
  L(i); U(j); L(i); D(j);
  L(i); U(j); L(i); D(j);
  L(i);
}

int main() {
  for (int i = 0; i < 6; ++i) {
    scanf("%s", s[i]);
    for (int j = 0; j < 6; ++j) {
      if ('a' <= s[i][j] && s[i][j] <= 'z') s[i][j] -= 'a';
      else s[i][j] = 26 + s[i][j] - '0';
    }
  }
  for (int i = 0; i < 6; ++i) for (int j = 0; j < 6; ++j) {
    int sx, sy;
    for (int x = 0; x < 6; ++x) for (int y = 0; y < 6; ++y) {
      if (s[x][y] == i * 6 + j) sx = x, sy = y;
    }
    if (i == sx && j == sy) continue;
    if (j < sy) {
      for (int k = sy; k > j; --k) swapr(sx, k - 1);
    } else if (j > sy) {
      for (int k = sy; k < j; ++k) swapr(sx, k);
    }
    for (int k = sx; k > i; --k) swapc(k - 1, j);
  }
  /*for (int i = 0; i < 6; ++i) {
    for (int j = 0; j < 6; ++j) {
      printf("%d ", (int)s[i][j]);
    }
    puts("");
  }*/
  return 0;
}

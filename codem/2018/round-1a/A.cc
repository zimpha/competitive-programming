#include <cstdio>
#include <string>

std::string grid[3][3] = {
  {"@!:", "ABC", "DEF"},
  {"GHI", "JKL", "MNO"},
  {"PQRS", "TUV", "WXYZ"}
};

const int N = 1e6 + 10;

char s[N];
int x[26], y[26];

int main() {
  int T;
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      for (auto &&c : grid[i][j]) {
        if (c >= 'A' && c <= 'Z') {
          x[c - 'A'] = i;
          y[c - 'A'] = j;
        }
      }
    }
  }
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    scanf("%s", s);
    int nx = 0, ny = 0, ret = 0;
    for (int i = 0; s[i]; ++i) {
      int c = s[i] - 'A';
      ret += abs(x[c] - nx) + abs(y[c] - ny);
      nx = x[c], ny = y[c];
    }
    printf("%d\n", ret);
  }
  return 0;
}
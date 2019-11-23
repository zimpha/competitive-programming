#include <cstdio>

const int N = 300 + 10;

char s[N][N];
int label[N][N];

int main() {
  int n, m, k;
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 0; i < n; ++i) {
    scanf("%s", s[i]);
    for (int j = 0; j < m; ++j) {
      if (s[i][j] == '#') label[i][j] = k--;
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 1; j < m; ++j) {
      if (!label[i][j] && label[i][j - 1]) label[i][j] = label[i][j - 1];
    }
    for (int j = m - 2; j >= 0; --j) {
      if (!label[i][j] && label[i][j + 1]) label[i][j] = label[i][j + 1];
    }
  }
  for (int j = 0; j < m; ++j) {
    for (int i = 1; i < n; ++i) {
      if (!label[i][j] && label[i - 1][j]) label[i][j] = label[i - 1][j];
    }
    for (int i = n - 2; i >= 0; --i) {
      if (!label[i][j] && label[i + 1][j]) label[i][j] = label[i + 1][j];
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (j) putchar(' ');
      printf("%d", label[i][j]);
    }
    puts("");
  }
  return 0;
}

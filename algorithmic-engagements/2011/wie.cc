#include <cstdio>
#include <vector>

const int N = 1000 + 10;

char s[N][N];

int main() {
  int n;
  scanf("%d", &n);
  std::vector<bool> row(n), col(n);
  for (int i = 0; i < n; ++i) {
    scanf("%s", s[i]);
    for (int j = 0; j < n; ++j) {
      if (s[i][j] == 'W') row[i] = col[j] = 1;
    }
  }
  for (int i = 0, j = 0; i < n; ++i) if (!row[i]) {
    while (j < n && col[j]) ++j;
    s[i][j] = 'W';
    col[j] = row[i] = 1;
  }
  for (int i = 0; i < n; ++i) puts(s[i]);
  return 0;
}

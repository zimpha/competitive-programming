#include <cstdio>
#include <algorithm>

const int N = 1000;

int A[N][N], B[N][N];

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      scanf("%d", &A[i][j]);
      B[i][j] = A[i][j];
    }
  }
  for (int i = n - 1; i >= 0; --i) {
    for (int j = m - 1; j >= 0; --j) {
      if (j < m - 1) B[i][j] = std::min(B[i][j], B[i][j + 1]);
      if (i < n - 1) B[i][j] = std::min(B[i][j], B[i + 1][j]);
      if (j < m - 1) A[i][j] = std::min(A[i][j], A[i][j + 1]);
    }
  }
  for (int i = 1; i < n; ++i) {
    for (int j = 0; j + 1 < m; ++j) {
      A[i][j] = std::min(A[i][j], A[i - 1][j + 1]);
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (j) putchar(' ');
      printf("%d", std::min(A[i][j], B[i][j]));
    }
    puts("");
  }
  return 0;
}

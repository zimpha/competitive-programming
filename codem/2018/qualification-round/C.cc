#include <cstdio>

const int N = 16;

double prob[N][N];
double dp[5][N];

int main() {
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      scanf("%lf", &prob[i][j]);
    }
    dp[0][i] = 1;
  }
  for (int i = 1; i <= 4; ++i) {
    for (int a = 0; a < N; ++a) {
      for (int b = 0; b < N; ++b) {
        int z = a ^ b;
        if ((z >> i) == 0 && (z >> (i - 1)) != 0) {
          dp[i][a] += dp[i - 1][a] * dp[i - 1][b] * prob[a][b];
        }
      }
    }
  }
  for (int i = 0; i < N; ++i) {
    if (i) putchar(' ');
    printf("%.10f", dp[4][i]);
  }
  puts("");
  return 0;
}

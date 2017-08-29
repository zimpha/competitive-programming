#pragma GCC optimize ("O3")
#pragma GCC target ("avx")

#include <cstdio>

const int N = 512, mod = 1e9 + 7;

int A[N][N], B[N][N], C[N][N];
int n, m, p;

int reduce(int *A, int *B, int n) {
  long long r = 0;
  int i = 0;
  for (i = 0; i + 8 <= n; i += 8) {
    r += 1ll * A[i] * B[i];
    r += 1ll * A[i + 1] * B[i + 1];
    r += 1ll * A[i + 2] * B[i + 2];
    r += 1ll * A[i + 3] * B[i + 3];
    r += 1ll * A[i + 4] * B[i + 4];
    r += 1ll * A[i + 5] * B[i + 5];
    r += 1ll * A[i + 6] * B[i + 6];
    r += 1ll * A[i + 7] * B[i + 7];
    r %= mod;
  }
  while (i < n) r += 1ll * A[i] * B[i], ++i;
  return r % mod;
}

int main() {
  scanf("%d%d%d", &n, &p, &m);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < p; ++j) {
      scanf("%d", &A[i][j]);
      A[i][j] = (A[i][j] + mod) % mod;
    }
  }
  for (int i = 0; i < p; ++i) {
    for (int j = 0; j < m; ++j) {
      scanf("%d", &B[j][i]);
      B[j][i] = (B[j][i] + mod) % mod;
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      int r = reduce(A[i], B[j], p);
      printf("%d ", r);
    }
    puts("");
  }
  return 0;
}

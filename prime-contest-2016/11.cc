#include <cstdio>
#include <cassert>

int A[3000][3000], B[3000][3000];

bool is_prime(int n) {
  if (n < 2) return false;
  if (n < 3) return true;
  if (n % 2 == 0) return false;
  for (int i = 3; i * i <= n; i += 2) {
    if (n % i == 0) return false;
  }
  return true;
}

int main() {
  int n, k, p;
  scanf("%d%d", &n, &k);
  for (p = (k + 2) / 2 + (k & 1); p <= k; ++p) {
    if (is_prime(p)) break;
  }
  int m = 1, s = 0, r = p;
  for (int i = 0; i < p; ++i) A[i][0] = i;
  for (; r < n; r *= p) {
    for (int i = 0; i < p; ++i) {
      for (int j = 0; j < r; ++j) {
        if (i * r + j < n)
          B[i * r + j][0] = i;
      }
    }
    for (int i = 0; i < p; ++i) {
      for (int j = 0; j < p; ++j) {
        for (int k = 0; k < r; ++k) {
          for (int l = 0; l < m; ++l) {
            if (i * r + k < n)
              B[i * r + k][j * m + l + 1] = (A[k][l] + i * j) % p;
          }
        }
      }
    }
    m = m * p + 1;
    s = s * p + 1;
    for (int i = 0; i < r * p && i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        A[i][j] = B[i][j];
      }
    }
  }
  printf("%d %d\n", m, s);
  assert(s * (k + 2) <= m * 2);
  assert(m <= n * 2);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      putchar('a' + A[i][j]);
    }
    puts("");
  }
  return 0;
}

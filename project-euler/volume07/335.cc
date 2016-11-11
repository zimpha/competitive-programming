#include <bits/stdc++.h>

long brute(int n) {
  std::vector<int> bowls(n, 1);
  long step = 1;
  for (int last = 0; bowls[last] != n; ) {
    int s = bowls[last];
    bowls[last] = 0;
    for (int i = 0; i < s; ++i) {
      last = (last + 1) % n;
      bowls[last] += 1;
    }
    step += 1;
  }
  return step;
}

void mul(long A[4][4], long B[4][4], long mod) {
  long C[4][4];
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      C[i][j] = 0;
      for (int k = 0; k < 4; ++k) {
        C[i][j] += A[i][k] * B[k][j];
      }
    }
  }
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      A[i][j] = C[i][j] % mod;
    }
  }
}

// f(n) = M(2^n + 1), f(n) = 9 * f(n-1) - 26 * f(n-2) + 24 * f(n-3)
long run(long n, long mod) {
  if (n == 0) return 2;
  if (n == 1) return 7;
  if (n == 2) return 22;
  long R[4] = {15, 5, 2, 22};
  long A[4][4] = {{9, mod - 26, 24, 0}, {1, 0, 0, 0}, {0, 1, 0, 0}, {9, mod - 26, 24, 1}};
  n -= 2;
  for (; n; n >>= 1) {
    if (n & 1) {
      long T[4];
      for (int i = 0; i < 4; ++i) {
        T[i] = 0;
        for (int j = 0; j < 4; ++j) {
          T[i] += A[i][j] * R[j];
        }
      }
      for (int i = 0; i < 4; ++i) R[i] = T[i] % mod;
    }
    mul(A, A, mod);
  }
  return R[3];
}

int main() {
  std::cout << run(3, 40353607) << std::endl;
  std::cout << run(1000000000000000000ll, 40353607) << std::endl;
  return 0;
}

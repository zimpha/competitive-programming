#include <bits/stdc++.h>

using LL = long long;

const int M = 100000000;

void mul(int A[4][4], int B[4][4]) {
  int C[4][4];
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      C[i][j] = 0;
      for (int k = 0; k < 4; ++k) {
        C[i][j] += 1ll * A[i][k] * B[k][j] % M;
      }
    }
  }
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      A[i][j] =  C[i][j];
    }
  }
}

LL run(LL n) {
  int A[4][4] = {{2, 2, M - 2, 1}, {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}};
  int R[4] = {8, 4, 1, 1};
  if (n <= 4) return R[n - 1];
  for (n -= 4; n; n >>= 1) {
    if (n & 1) {
      int tmp[4];
      for (int i = 0; i < 4; ++i) {
        tmp[i] = 0;
        for (int j = 0; j < 4; ++j) {
          tmp[i] += 1ll * A[i][j] * R[j] % M;
          tmp[i] %= M;
        }
      }
      for (int i = 0; i < 4; ++i) R[i] = tmp[i];
    }
    mul(A, A);
  }
  return R[0];
}

int main() {
  std::cout << run(10) << std::endl;
  std::cout << run(1000000000000ll) << std::endl;
  return 0;
}

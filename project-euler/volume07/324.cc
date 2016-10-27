//A028452
#include <bits/stdc++.h>

const int mod = 100000007, N = 23;

void mul(long A[N][N], long B[N][N]) {
  static long C[N][N];
  memset(C, 0, sizeof(C));
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      for (int k = 0; k < N; ++k) {
        C[i][j] += A[i][k] * B[k][j];
      }
      C[i][j] %= mod;
    }
  }
  memcpy(A, C, sizeof(C));
}

void mul(long C[N][N], long A[N][N], long B[N][N]) {
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      C[i][j] = 0;
      for (int k = 0; k < N; ++k) {
        C[i][j] += A[i][k] * B[k][j];
      }
      C[i][j] %= mod;
    }
  }
}

long run() {
  long R[N] = {1, 229, 117805, 64647289, 69563725, 96149360, 40041351, 13625499, 49444743, 7047816, 63444149, 71774943, 18904145, 72062, 58262981, 68125412, 64015488, 12253197, 9101639, 63312159, 47925805, 75412110, 81862504};
  long C[N] = {679, 99923830, 3519127, 14088452, 35862961, 76806653, 56470433, 33422571, 39262562, 84928070, 25900794, 74099213, 15071937, 60737445, 66577436, 43529574, 23193354, 64137046, 85911555, 96480880, 76177, 99999328, 1};
  std::reverse(R, R + N);
  long A[N][N], t2[N][N], t4[N][N], t8[N][N], I[N][N], B[N][N];
  memset(A, 0, sizeof(A));
  memset(I, 0, sizeof(I));
  for (int i = 0; i < N; ++i) I[i][i] = 1;
  for (int i = 1; i < N; ++i) A[i][i - 1] = 1;
  for (int i = 0; i < N; ++i) A[0][i] = C[i];
  memcpy(B, A, sizeof(A));
  for (int i = 3; i < 10000; ++i) {
    mul(t2, A, A); // 2
    mul(t4, t2, t2); // 4
    mul(t8, t4, t4); // 8
    mul(I, t8);
    mul(I, A);
    mul(A, t2, t8);
  }
  mul(t2, A, A);
  mul(t4, t2, t2);
  mul(I, t4);
  for (int i = 0; i < 2; ++i) {
    mul(t2, I, I); // 2
    mul(t4, t2, t2); // 4
    mul(t8, t4, t4); // 8
    mul(I, t2, t8);
  }
  for (int i = 0; i < 78; ++i) mul(I, B);
  long ret = 0;
  for (int i = 0; i < N; ++i) ret += R[i] * I[0][i];
  return ret % mod;
}

int main() {
  std::cout << run() << std::endl;
  return 0;
}

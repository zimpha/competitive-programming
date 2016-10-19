#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 24 * 23, M = 1e9;

typedef int Matrix[N][N];
void mul(Matrix A, Matrix B) {
  static Matrix C;
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      C[i][j] = 0;
      for (int k = 0; k < N; ++k) {
        C[i][j] += 1ll * A[i][k] * B[k][j] % M;
        if (C[i][j] >= M) C[i][j] -= M;
      }
    }
  }
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      A[i][j] = C[i][j];
    }
  }
}

LL run(LL n) {
  Matrix A; memset(A, 0, sizeof(A));
  for (int s = 0; s <= 23; ++s) {
    for (int m = 0; m < 23; ++m) {
      int u = s * 23 + m;
      for (int d = 0; d < 10; ++d) if (s + d <= 23) {
        int v = (s + d) * 23 + (m * 10 + d) % 23;
        A[v][u] += 1;
      }
    }
  }
  int R[N]; memset(R, 0, sizeof(R)); R[0] = 1;
  for (; n; n >>= 1) {
    if (n & 1) {
      int tmp[N];
      for (int i = 0; i < N; ++i) {
        tmp[i] = 0;
        for (int j = 0; j < N; ++j) {
          tmp[i] += 1ll * A[i][j] * R[j] % M;
          if (tmp[i] >= M) tmp[i] -= M;
        }
      }
      for (int i = 0; i < N; ++i) R[i] = tmp[i];
    }
    mul(A, A);
  }
  return R[23 * 23];
}

int main() {
  cout << run(9) << endl;
  cout << run(42) << endl;
  cout << run(3138428376721) << endl;
  return 0;
}

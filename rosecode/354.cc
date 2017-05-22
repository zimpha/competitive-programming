#include <bits/stdc++.h>

typedef std::vector<long> vec_t;
const long mod = 1000000000000000ll;

long mul_mod(long a, long b) {
  long r = 0;
  for (; b; b >>= 1) {
    if (b & 1) r = (r + a) % mod;
    a = (a + a) % mod;
  }
  return r;
}

void mul(long A[3][3], long B[3][3]) {
  static long C[3][3];
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      C[i][j] = 0;
      for (int k = 0; k < 3; ++k) {
        C[i][j] = (C[i][j] + mul_mod(A[i][k], B[k][j])) % mod;
      }
    }
  }
  memcpy(A, C, sizeof(C));
}

vec_t operator + (const vec_t &A, const vec_t &B) {
  vec_t C(3, 0);
  for (int i = 0; i < 3; ++i) {
    C[i] = (A[i] + B[i]) % mod;
  }
  return C;
}

vec_t operator * (const vec_t &A, long x) {
  vec_t C(A);
  for (int i = 0; i < 3; ++i) {
    C[i] = mul_mod(C[i], x);
  }
  return C;
}

void run(long n) {
  vec_t R[3] = {{65601, 67402, 83802}, {791, 812, 1010}, {9, 10, 12}};
  long A[3][3] = {{82, 82, mod - 1}, {1, 0, 0}, {0, 1, 0}};
  n -= 3;
  for (; n; n >>= 1) {
    if (n & 1) {
      vec_t T[3];
      for (int i = 0; i < 3; ++i) {
        T[i] = {0, 0, 0};
        for (int j = 0; j < 3; ++j) {
          T[i] = T[i] + R[j] * A[i][j];
        }
      }
      for (int i = 0; i < 3; ++i) R[i] = T[i];
    }
    mul(A, A);
  }
  std::cout << R[0][0] << ',' << R[0][1] << ',' << R[0][2] << std::endl;
}

int main() {
  run(4);
  run(123456789101112ll);
  return 0;
}

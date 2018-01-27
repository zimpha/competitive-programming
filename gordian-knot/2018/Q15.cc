#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

const int N = 243, mod = 1e9 + 7;

using int64 = long long;

void mul(int64 A[N][N], int64 B[N][N]) {
  static int64 C[N][N];
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      C[i][j] = 0;
      for (int k = 0; k < N; ++k) {
        C[i][j] = (C[i][j] + A[i][k] * B[k][j] % mod);
      }
      C[i][j] %= mod;
    }
  }
  memcpy(A, C, sizeof(C));
}

int main() {
  int64 R[N];
  std::vector<int> v;
  for (int i = 0; i < N; ++i) {
    int t[5];
    for (int j = 0, m = i; j < 5; ++j) {
      t[j] = m % 3;
      m /= 3;
    }
    bool flag = true;
    for (int j = 1; j < 5; ++j) {
      if (t[j - 1] + t[j] == 1) flag = false;
    }
    R[i] = flag;
    if (flag) v.push_back(i);
  }
  printf("%d\n", (int)v.size());
  int64 A[N][N];
  memset(A, 0, sizeof(A));
  for (auto &&x: v) for (auto &&y: v) {
    int a[5], b[5];
    for (int i = 0, m = x; i < 5; ++i) {
      a[i] = m % 3;
      m /= 3;
    }
    for (int i = 0, m = y; i < 5; ++i) {
      b[i] = m % 3;
      m /= 3;
    }
    bool flag = true;
    for (int i = 0; i < 5; ++i) {
      if (a[i] + b[i] == 1) flag = false;
    }
    A[x][y] = flag;
  }
  int64 n;
  scanf("%lld", &n);
  --n;
  //int64 n = 1000000000000000000ll - 1;
  for (; n; n >>= 1) {
    if (n & 1) {
      static int64 T[N];
      for (int i = 0; i < N; ++i) {
        T[i] = 0;
        for (int j = 0; j < N; ++j) {
          T[i] += A[i][j] * R[j] % mod;
        }
        T[i] %= mod;
      }
      memcpy(R, T, sizeof(T));
    }
    mul(A, A);
  }
  int64 ret = 0;
  for (int i = 0; i < N; ++i) {
    ret += R[i];
  }
  printf("%lld\n", ret % mod);
  return 0;
}

#include <cstdio>
#include <cstring>

using int64 = long long;
const int mod = 1e9 + 7;

void mul(int64 a[3][3], int64 b[3][3]) {
  int64 c[3][3];
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      c[i][j] = (a[i][0] * b[0][j] + a[i][1] * b[1][j] + a[i][2] * b[2][j]) % mod;
    }
  }
  memcpy(a, c, sizeof(c));
}

int main() {
  int64 n;
  while (scanf("%lld", &n) == 1) {
    int64 r[] = {1, 0, 0};
    int64 a[3][3];
    memset(a, 0, sizeof(a));
    for (int i = 0; i < 3; ++i) {
      for (int o = 0; o < 2; ++o) {
        a[(i * 2 + o) % 3][i]++;
      }
    }
    for (; n; n >>= 1) {
      if (n & 1) {
        int64 t[3];
        for (int i = 0; i < 3; ++i) {
          t[i] = a[i][0] * r[0] + a[i][1] * r[1] + a[i][2] * r[2];
        }
        for (int i = 0; i < 3; ++i) r[i] = t[i] % mod;
      }
      mul(a, a);
    }
    printf("%lld\n", r[0]);
  }
  return 0;
}

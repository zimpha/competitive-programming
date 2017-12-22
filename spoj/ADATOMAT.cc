#include <cstdio>
#include <cstring>

using int64 = long long;

constexpr int U = 1 << 16, mod = 1e9 + 7, N = 2e7 + 10;

int X[N], Y[N];
int cx[U], cy[U];

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, a, b;
    scanf("%d%d%d%d", &n, &a, &b, &X[0]);
    memset(cx, 0, sizeof(cx));
    memset(cy, 0, sizeof(cy));
    for (int i = 1; i < n; ++i) {
      X[i] = ((int64)X[i - 1] * a + b) % mod;
    }
    for  (int i = 0; i < n; ++i) {
      cx[X[i] & (U - 1)]++;
      cy[X[i] >> 16]++;
    }
    for (int i = 1; i < U; ++i) {
      cy[i] += cy[i - 1];
      cx[i] += cx[i - 1];
    }
    for (int i = n - 1; i >= 0; --i) {
      Y[--cx[X[i] & (U - 1)]] = X[i];
    }
    for (int i = n - 1; i >= 0; --i) {
      X[--cy[Y[i] >> 16]] = Y[i];
    }
    int ret = 0;
    for (int i = 0; i < n; ++i) {
      ret += (int64)X[i] * (i + 1) % mod;
      if (ret >= mod) ret -= mod;
    }
    printf("%d\n", ret);
  }
  return 0;
}

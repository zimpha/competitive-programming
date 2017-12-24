#include <cstdio>

using int64 = long long;
const int N = 1e7 + 1, mod = 1e9 + 7;

int64 a[N];

int main() {
  a[0] = a[1] = 1;
  for (int n = 4; n < N; ++n) {
    a[n] = ((n + 1) * a[n - 1] - (n - 2) * a[n - 2] - (n - 5) * a[n - 3] + (n - 3) * a[n - 4]) % mod;
    if (a[n] < 0) a[n] += mod;
  }
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    printf("%lld\n", a[n]);
  }
  return 0;
}

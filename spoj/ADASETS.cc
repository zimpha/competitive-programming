#include <cstdio>

using int64 = long long;
constexpr int N = 1e7, mod = 1e9 + 7;

int phi[N + 1], a[N + 1], inv[N + 1];
int p[10000], m;

int main() {
  phi[1] = inv[1] = a[0] = 1;
  for (int i = 1; i <= N; ++i) {
    a[i] = 2 * a[i - 1];
    if (a[i] >= mod) a[i] -= mod;
  }
  for (int i = 2, j, u, v; i <= N; ++i) {
    inv[i] = int64(mod - mod / i) * inv[mod % i] % mod;
    if (!phi[i]) {
      if (i <= N / i) p[m++] = i;
      phi[i] = i - 1;
    }
    for (j = 0, u = N / i; j < m && p[j] <= u; ++j) {
      if (i % (v = p[j])) {
        phi[i * v] = phi[i] * (v - 1);
      } else {
        phi[i * v] = phi[i] * v;
        break;
      }
    }
    u = 2, v = phi[i];
    for (j = i; j <= N; j += i) {
      a[j] += (int64)v * u % mod;
      if (a[j] >= mod) a[j] -= mod;
      u = u * 2; if (u >= mod) u -= mod;
    }
  }
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    printf("%lld\n", (int64)a[n] * inv[n] % mod);
  }
  return 0;
}

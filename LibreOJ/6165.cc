#include <cstdio>

const int N = 100000000 + 10, mod = 1e8 + 7;

int p[10000], m;
bool mark[N];

int main() {
  int n;
  scanf("%d", &n);
  int r = 1;
  for (int i = 2; i <= n; ++i) {
    if (!mark[i]) {
      if (i <= n / i) p[m++] = i;
      else r = 1ll * r * i % mod;
    }
    for (int j = 0; j < m && p[j] <= n / i; ++j) {
      mark[i * p[j]] = 1;
      if (i % p[j] == 0) break;
    }
  }
  for (int i = 0; i < m; ++i) {
    for (int v = 1; v <= n / p[i]; v *= p[i]) {
      r = 1ll * r * p[i] % mod;
    }
  }
  printf("%d\n", r);
  return 0;
}

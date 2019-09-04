#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int mod = 999999599;
const int phi = mod - 1;
const int N = 2e5 + 10;

using int64 = long long;

int g[1000];
int64 p[N];

// produce first n terms in O(n \sqrt n)
void run(int mx) {
  for (int i = 0; i < 900; ++ i) {
    int k = (i & 1) ? -i / 2 - 1 : i / 2 + 1;
    g[i] = k * (3 * k - 1) / 2;
  }
  p[0] = 1;
  for (int n = 1, m = 0; n <= mx; ++ n) {
    while (g[m] <= n) ++m;
    for (int i = 0; i < m; ++i) {
      if ((i >> 1) & 1) p[n] -= p[n - g[i]];
      else p[n] += p[n - g[i]];
    }
    p[n] = (p[n] % phi + phi) % phi;
  }
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  run(n);
  n = p[n] + phi;
  int ret = 1;
  for (; n; n >>= 1) {
    if (n & 1) ret = 1ll * ret * m % mod;
    m = 1ll * m * m % mod;
  }
  printf("%d\n", ret);
  return 0;
}

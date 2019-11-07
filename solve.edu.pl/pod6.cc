#include <cstdio>
#include <vector>

using int64 = long long;

const int N = 3e5 + 10, mod = 1e9 + 7;

int64 p[N];
int g[1000];

int main() {
  for (int i = 0; i < 900; ++ i) {
    int k = (i & 1) ? -i / 2 - 1 : i / 2 + 1;
    g[i] = k * (3 * k - 1) / 2;
  }
  int T, mx = 0;
  scanf("%d", &T);
  std::vector<int> ns(T);
  for (int i = 0; i < T; ++i) {
    scanf("%d", &ns[i]);
    if (ns[i] > mx) mx = ns[i];
  }
  p[0] = 1;
  for (int n = 1, m = 0; n <= mx; ++ n) {
    while (g[m] <= n) ++m;
    for (int i = 0; i < m; ++i) {
      if ((i >> 1) & 1) p[n] -= p[n - g[i]];
      else p[n] += p[n - g[i]];
    }
    p[n] = (p[n] % mod + mod) % mod;
  }
  for (auto &n: ns) {
    printf("%lld\n", p[n]);
  }
  return 0;
}

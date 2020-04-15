#include <cstdio>
#include <vector>

using int64 = long long;

const int mod = 1e9 + 7;
const int N = 5000 + 10;

char s[N];

int64 pow_mod(int64 a, int64 n) {
  int64 r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % mod;
    a = a * a % mod;
  }
  return r;
}

int main() {
  int n, a, b, r, h;
  scanf("%d%d%d", &n, &r, &h);
  scanf("%s%d%d", s, &a, &b);
  int64 p = pow_mod(r + h, mod - 2) * r % mod;
  int64 q = pow_mod(r + h, mod - 2) * h % mod;
  std::vector<int> prefix(n + 1), suffix(n + 1);
  std::vector<int> f(n + 1), g(n + 1);
  f[b] = 1; prefix[0] = f[0];
  for (int i = 0; i < n; ++i) {
    g.assign(n + 1, 0);
    if (s[i] == 'R') {
      for (int j = 1; j <= n; ++j) {
        g[j] = (f[j] * p + g[j - 1] * q) % mod;
      }
    } else {
      for (int j = 0; j < n; ++j) g[j] = f[j + 1];
    }
    f.swap(g);
    prefix[i + 1] = f[0];
  }
  f.assign(n + 1, 0); g.assign(n + 1, 0);
  f[a] = 1; suffix[n] = f[0];
  for (int i = n - 1; i >= 0; --i) {
    g.assign(n + 1, 0);
    if (s[i] == 'H') {
      for (int j = 1; j <= n; ++j) {
        g[j] = (f[j] * q + g[j - 1] * p) % mod;
      }
    } else {
      for (int j = 0; j < n; ++j) g[j] = f[j + 1];
    }
    f.swap(g);
    suffix[i] = f[0];
  }
  int64 ret = 0;
  for (int i = 0; i <= n; ++i) {
    ret += (int64)prefix[i] * suffix[i] % mod;
  }
  printf("%lld\n", ret % mod);
  return 0;
}

#include <cstdio>
#include <utility>

const int N = 5000 + 10, mod = 1e9 + 7;

using int64 = long long;

inline int64 mul_mod(int64 a, int64 b, int64 mod) {
  if (mod < int(1e9)) return a * b % mod;
  int64 k = (int64)((long double)a * b / mod);
  int64 res = a * b - k * mod;
  res %= mod;
  if (res < 0) res += mod;
  return res;
}

using pii = std::pair<int64, int>;

int64 x[N], y[N];
int64 x0[N], a[N], b[N], c[N];
pii q[N][N];
int h[N], t[N];

int main() {
  int n, k;
  scanf("%d%d", &n, &k);
  for (int i = 0; i < n; ++i) {
    scanf("%lld%lld%lld%lld", &x0[i], &a[i], &b[i], &c[i]);
    x[i] = x0[i];
    a[i] %= c[i], b[i] %= c[i], x0[i] %= c[i];
    h[i] = 0, t[i] = -1;
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j + 1 < k; ++j) {
      while (h[i] <= t[i] && x[i] <= q[i][t[i]].first) --t[i];
      q[i][++t[i]] = {x[i], j};
      x0[i] = mul_mod(x0[i], a[i], c[i]) + b[i];
      if (x0[i] >= c[i]) x0[i] -= c[i];
      x[i] = x0[i];
    }
  }
  int64 ret = 0;
  for (int j = k - 1; j < n; ++j) {
    for (int i = 0; i < n; ++i) {
      while (h[i] <= t[i] && x[i] <= q[i][t[i]].first) --t[i];
      q[i][++t[i]] = {x[i], j};
      while (h[i] <= t[i] && q[i][h[i]].second <= j - k) ++h[i];
      y[i] = q[i][h[i]].first;
      x0[i] = mul_mod(x0[i], a[i], c[i]) + b[i];
      if (x0[i] >= c[i]) x0[i] -= c[i];
      x[i] = x0[i];
    }
    static pii p[N];
    int a = 0, b = -1;
    for (int i = 0; i + 1 < k; ++i) {
      while (a <= b && y[i] <= p[b].first) --b;
      p[++b] = {y[i], i};
    }
    for (int i = k - 1; i < n; ++i) {
      while (a <= b && y[i] <= p[b].first) --b;
      p[++b] = {y[i], i};
      while (a <= b && p[a].second <= i - k) ++a;
      ret += p[a].first % mod;
    }
  }
  printf("%lld\n", ret % mod);
  return 0;
}

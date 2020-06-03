#include <cstdio>
#include <cstring>
#include <vector>
#include <cassert>
#include <algorithm>

using int64 = long long;
const int mod = 998244353;

using vec = std::vector<int64>;

struct Vec {
  vec x;
  int64 w;
} one, zero;

// x[m + 1] = \sum_{i=1}^{m} c[i] * x[i] + 1
// x[u] = \sum_{i=1}^{m} a[i] * x[i] + w_a
// x[v] = \sum_{i=1}^{m} b[i] * x[i] + w_b
// find x[u + v] = \sum_{i=0}^{m-1} s[i] * x[i] + w_s
Vec mul(const Vec &a, const Vec &b, const vec &c) {
  int m = c.size();
  std::vector<int64> s(m * 2);
  int64 w = a.w;
  for (int i = 0; i < m; ++i) w += a.x[i] * b.w % mod;
  for (int i = 0; i < m; ++i) for (int j = 0; j < m; ++j) {
    s[i + j] += a.x[i] * b.x[j] % mod;
  }
  for (int i = 2 * m - 1; i >= m; --i) {
    s[i] %= mod; w += s[i];
    for (int j = 1; j <= m; ++j) s[i - j] += c[m - j] * s[i] % mod;
  }
  for (int i = 0; i < m; ++i) s[i] %= mod;
  return {vec(s.begin(), s.begin() + m), w % mod};
}

int64 pow_mod(int64 a, int64 n) {
  int64 r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % mod;
    a = a * a % mod;
  }
  return r;
}

Vec calc(int64 n, const vec& c) {
  Vec r = zero, a = one;
  for (int64 x = 1; n; n >>= 1, x <<= 1) {
    if (n & 1) r = mul(r, a, c);
    a = mul(a, a, c);
  }
  return r;
}

const int N = 500 + 10;
int64 a[N][N], aa[N][N], b[N], bb[N];

bool gauss(int n) {
  for (int k = 0, i, j, s; k < n; ++k) {
    for (s = k, i = k + 1; i < n; ++i) {
      if (a[i][k]) s = i;
    }
    if (!a[s][k]) return false;
    if (s != k) {
      std::swap(b[s], b[k]);
      for (i = k; i < n; ++i) {
        std::swap(a[s][i], a[k][i]);
      }
    }
    for (j = k + 1; j < n; ++j) {
      int64 t = mod - a[j][k] * pow_mod(a[k][k], mod - 2) % mod;
      b[j] += b[k] * t % mod;
      if (b[j] >= mod) b[j] -= mod;
      for (i = k + 1; i < n; ++i) {
        a[j][i] += t * a[k][i] % mod;
        if (a[j][i] >= mod) a[j][i] -= mod;
      }
    }
  }
  for (int i = n - 1; i >= 0; --i) {
    b[i] = b[i] * pow_mod(a[i][i], mod - 2) % mod;
    for (int j = 0; j < i; ++j) {
      b[j] -= a[j][i] * b[i] % mod;
      if (b[j] < 0) b[j] += mod;
    }
  }
  return true;
}

int main() {
  int64 m, k;
  int n;
  scanf("%d%lld%lld\n", &n, &m, &k);
  std::vector<int64> c(n);
  {
    std::vector<int> a(n);
    int64 sum = 0;
    for (int i = 0; i < n; ++i) {
      scanf("%d", &a[i]);
      sum += a[i];
    }
    sum = pow_mod(sum, mod - 2);
    for (int i = 0; i < n; ++i) c[i] = a[i] * sum % mod;
    std::reverse(c.begin(), c.end());
  }
  if (n == 1) {
    printf("%lld\n", k % mod);
    return 0;
  }
  zero = {vec(n), 0}; zero.x[0] = 1;
  one = {vec(n), 0}; one.x[1] = 1;

  std::vector<Vec> t = {calc(m - n, c)};
  for (int i = 1; i < n - 1; ++i) {
    t.push_back(mul(t.back(), one, c));
  }
  memset(a, 0, sizeof(a));
  memset(b, 0, sizeof(b));
  for (int i = 0; i < n; ++i) {
    b[i] = 1; a[i][i] = 1;
    for (int j = 0; j < n; ++j) {
      int x = i - j;
      if (x == 0) continue;
      else if (x > 0) {
        a[i][x - 1] -= c[n - 1 - j];
      } else {
        x = n - 1 + x;
        b[i] += t[x].w * c[n - 1 - j] % mod;
        for (int y = 0; y < n; ++y) {
          a[i][y] -= t[x].x[y] * c[n - 1 - j] % mod;
        }
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    b[i] %= mod; b[i] += mod; b[i] %= mod;
    for (int j = 0; j < n; ++j) {
      a[i][j] %= mod; a[i][j] += mod; a[i][j] %= mod;
    }
  }
  gauss(n);
  auto r = calc(k - 1, c);
  int64 ret = r.w;
  for (int i = 0; i < n; ++i) {
    ret += r.x[i] * b[i] % mod;
  }
  printf("%lld\n", ret % mod);
  return 0;
}

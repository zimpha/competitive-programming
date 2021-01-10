#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using i64 = long long;

const int N = 500 + 10, mod = 1e9 + 7;

template<typename T>
T gcd(T a, T b) {
  return !b ? a : gcd(b, a % b);
}

// return x, where ax = 1 (mod mod)
i64 mod_inv(i64 a) {
  if (gcd<i64>(a, mod) != 1) return -1;
  i64 b = mod, s = 1, t = 0;
  while (b) {
    i64 q = a / b;
    std::swap(a -= q * b, b);
    std::swap(s -= q * t, t);
  }
  return s < 0 ? s + mod : s;
}

std::vector<i64> Hessenberg(int n, i64 m[N][N]) {
  // reduce into upper Hessenberg form while preserving the characteristic polynomial
  for (int j = 1, i; j <= n - 2; ++j) {
    for (i = j + 1; i < n && !m[i][j - 1]; ++i);
    if (i == n) continue;
    if (m[j][j - 1] == 0) {
      for (int k = 0; k < n; ++k) std::swap(m[i][k], m[j][k]);
      for (int k = 0; k < n; ++k) std::swap(m[k][i], m[k][j]);
    }
    i64 inv = mod_inv(m[j][j - 1]);
    for (int k = j + 1; k < n; ++k) {
      i64 u = m[k][j - 1] * inv % mod;
      for (int i = 0; i < n; ++i) {
        m[k][i] = (m[k][i] - u * m[j][i] % mod + mod) % mod;
        m[i][j] = (m[i][j] + u * m[i][k]) % mod;
      }
    }
  }
  // find the characteristic polynomial
  std::vector<std::vector<i64>> p(n + 1); p[0] = {1};
  for (int k = 1; k <= n; ++k) {
    p[k].assign(p[k - 1].size() + 1, 0);
    for (int i = 0; i < (int)p[k - 1].size(); ++i) {
      p[k][i] += p[k - 1][i] * (mod - m[k - 1][k - 1]) % mod;
      p[k][i + 1] += p[k - 1][i];
    }
    for (auto &x: p[k]) x %= mod;
    i64 t = 1;
    for (int i = 1; i < k; ++i) {
      t = t * m[k - i][k - i - 1] % mod;
      i64 mul = (mod - t) * m[k - i - 1][k - 1] % mod;
      for (int j = 0; j < (int)p[k - i - 1].size(); ++j) {
        p[k][j] = (p[k][j] + mul * p[k - i - 1][j]) % mod;
      }
    }
  }
  return {p[n].begin() + 1, p[n].end()};
}

i64 a[N][N];

std::vector<i64> poly_mod(const std::vector<i64> &p, const std::vector<i64> &pmod) {
  std::vector<i64> r(p);
  while (r.size() >= pmod.size()) {
    i64 m = (mod - r.back()) % mod;
    for (size_t i = 0; i < pmod.size(); ++i) {
      r[r.size() - pmod.size() + i] += pmod[i] * m % mod;
      r[r.size() - pmod.size() + i] %= mod;
    }
    while (r.size() > 1 && r.back() == 0) r.pop_back();
  }
  return r;
}

std::vector<i64> poly_mul(const std::vector<i64> &a, const std::vector<i64> &b) {
  if (a.empty() || b.empty()) return {};
  std::vector<i64> c(a.size() + b.size() - 1, 0);
  for (size_t i = 0; i < a.size(); ++i) {
    for (size_t j = 0; j < b.size(); ++j) {
      c[i + j] += a[i] * b[j] % mod;
    }
  }
  for (auto &x: c) x %= mod;
  return c;
}

std::vector<i64> poly_add(const std::vector<i64> &a, const std::vector<i64> &b) {
  std::vector<i64> c(std::max(a.size(), b.size()), 0);
  for (size_t i = 0; i < c.size(); ++i) {
    c[i] += (i < a.size() ? a[i] : 0);
    c[i] += (i < b.size() ? b[i] : 0);
    c[i] %= mod;
  }
  return c;
}

void mul(std::vector<i64> a[2][2], std::vector<i64> b[2][2], const std::vector<i64> &pmod) {
  std::vector<i64> c[2][2];
  for (int i = 0; i < 2; ++i) for (int j = 0; j < 2; ++j) {
    c[i][j] = poly_add(poly_mul(a[i][0], b[0][j]), poly_mul(a[i][1], b[1][j]));
  }
  for (int i = 0; i < 2; ++i) for (int j = 0; j < 2; ++j) {
    a[i][j] = poly_mod(c[i][j], pmod);
  }
}

i64 resultant(std::vector<i64> a, std::vector<i64> b) {
  if (!a[0] || !b[0]) return 0;
  i64 ret = 1;
  while (true) {
    int n = a.size() - 1, m = b.size() - 1;
    if (n > m) {
      std::swap(n, m);
      std::swap(a, b);
      if ((n & 1) && (m & 1)) ret = mod - ret;
    }
    if (!n) {
      for (int i = 0; i < m; ++i) ret = ret * a[0] % mod;
      return ret;
    }
    i64 mul = mod - mod_inv(a.back()) * b.back() % mod;
    for (int i = 0; i <= n; ++i) {
      b[m - n + i] += a[i] * mul % mod;
      b[m - n + i] %= mod;
    }
    while (b.size() > 1 && b.back() == 0) {
      ret = ret * a[n] % mod;
      b.pop_back();
    }
  }
  return ret;
}

int main() {
  int n, m;
  i64 k;
  scanf("%d%d%lld", &n, &m, &k);
  if (n == 1) {
    puts("1");
    return 0;
  }

  for (int i = 0; i < m; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    --u, --v;
    a[u][v] = a[v][u] = mod - 1;
    a[u][u]++, a[v][v]++;
  }
  auto p = Hessenberg(n, a);
  if (!p[0]) {
    puts("0");
    return 0;
  }

  // path_k % p
  std::vector<i64> base[2][2], res[2][2];
  base[0][0] = {2, 1};
  base[0][1] = {mod - 1};
  base[1][0] = {1};
  base[1][1] = {};
  res[1][0] = res[0][1] = {};
  res[0][0] = res[1][1] = {1};
  for (; k; k >>= 1) {
    if (k & 1) mul(res, base, p);
    mul(base, base, p);
  }
  auto q = res[1][0];

  i64 ret = p[0];
  if (n % 2 == 0) ret = mod - ret;
  ret = ret * resultant(p, q) % mod * mod_inv(n) % mod;
  printf("%lld\n", ret);
  return 0;
}

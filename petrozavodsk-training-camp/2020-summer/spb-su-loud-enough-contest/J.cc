#include <cstdio>
#include <vector>
#include <algorithm>

using i64 = long long;

const int N = 30, M = 6000 + 10, mod = 998244353;

i64 fac[M], ifac[M], inv[M];
i64 matrix[N][N];

i64 pow_mod(i64 a, i64 n) {
  i64 r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % mod;
    a = a * a % mod;
  }
  return r;
}

i64 det(i64 a[][N], int n) {
  i64 sign = 1, ret = 1;
  for (int i = 0; i < n; ++i) {
    int r = i;
    while (r < n && a[r][i] == 0) ++r;
    if (r == n) return 0;
    if (r != i) {
      sign *= -1;
      for (int j = 0; j < n; ++j) {
        std::swap(a[r][j], a[i][j]);
      }
    }
    ret = ret * a[i][i] % mod;
    i64 inv = pow_mod(a[i][i], mod - 2);
    for (int j = i + 1; j < n; ++j) if (a[j][i]) {
      i64 mul = mod - a[j][i] * inv % mod;
      for (int k = i; k < n; ++k) {
        a[j][k] = (a[j][k] + mul * a[i][k]) % mod;
      }
    }
  }
  if (sign == -1) ret = mod - ret;
  return ret;
}

std::vector<i64> interpolation(const i64 w[], int n){
  std::vector<i64> u(w, w + n), ret(n), sum(n);
  ret[0] = u[0], sum[0] = 1;
  for (int i = 1; i < n; ++i) {
    for (int j = n - 1; j >= i; --j) {
      u[j] = (u[j] - u[j - 1] + mod) * inv[i] % mod;
    }
    for (int j = i; j; --j) {
      sum[j] = ((mod - sum[j]) * (i - 1) + sum[j - 1]) % mod;
      ret[j] = (ret[j] + sum[j] * u[i]) % mod;
    }
    sum[0] = (mod - sum[0]) * (i - 1) % mod;
    ret[0] = (ret[0] + sum[0] * u[i]) % mod;
  }
  return ret;
}

i64 eval(const std::vector<i64> &coef, i64 x) {
  i64 w = 1, ret = 0;
  for (auto &c: coef) {
    ret += c * w % mod;
    w = w * x % mod;
  }
  return ret % mod;
}

std::vector<i64> poly[300];

void prepare() {
  fac[0] = ifac[0] = fac[1] = ifac[1] = inv[1] = 1;
  for (int i = 2; i < M; ++i) {
    fac[i] = fac[i - 1] * i % mod;
    inv[i] = (mod - mod / i) * inv[mod % i] % mod;
    ifac[i] = ifac[i - 1] * inv[i] % mod;
  }
  for (int d = 0; d < 300; ++d) {
    for (int i = 0; i <= d / 2; ++i) {
      i64 w = ifac[i] * ifac[d - i * 2] % mod;
      if (i % 2 == 1) w = mod - w;
      poly[d].push_back(w);
    }
  }
}

int main() {
  prepare();
  int n, m = 0;
  scanf("%d", &n);
  std::vector<int> a(n), b(n);
  for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
  for (int i = 0; i < n; ++i) scanf("%d", &b[i]);
  for (int i = 0; i < n; ++i) {
    m += b[i] - a[i];
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < i; ++j) {
      if ((a[i] - a[j]) * (b[i] - b[j]) < 0) {
        puts("0");
        return 0;
      }
    }
  }
  if (m < 0 || m % 2 == 1) {
    puts("0");
    return 0;
  }
  std::vector<i64> w(m / 2 + 1);
  for (int s = 0; s <= m / 2; ++s) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        int d = b[j] - a[i];
        if (d < 0) matrix[i][j] = 0;
        else matrix[i][j] = eval(poly[d], s);
      }
    }
    w[s] = det(matrix, n);
  }

  auto coef = interpolation(w.data(), w.size());
  i64 ret = 0;
  for (int x = 0; x <= m / 2; ++x) {
    i64 w = fac[m / 2] * fac[m - x * 2] % mod * ifac[m / 2 - x] % mod;
    ret += w * coef[x] % mod;
  }
  ret %= mod;
  printf("%lld\n", ret * pow_mod((mod + 1) / 2, m / 2) % mod);
  return 0;
}

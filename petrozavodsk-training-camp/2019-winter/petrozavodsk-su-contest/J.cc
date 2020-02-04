#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using int64 = long long;

const int N = 51;
const int mod = 998244353;

int64 fac[N], ifac[N];
int64 f[N][N][N];
int64 pw[N * N];
char s[N * N];

int64 pow_mod(int64 a, int64 n) {
  int64 r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % mod;
    a = a * a % mod;
  }
  return r;
}

int64 binom(int n, int m) {
  return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}

int div_mod(int &n, char d[], int mod) {
  int64 x = 0;
  for (int i = n - 1; i >= 0; --i) {
    x = x * 10 + d[i];
    d[i] = x / mod;
    x %= mod;
  }
  while (n && d[n - 1] == 0) --n;
  return x;
}

int main() {
  int m, b, c;
  scanf("%d%d%d", &m, &b, &c);
  scanf("%s", s);
  int64 n_mod = 0;
  int n = strlen(s);
  for (int i = 0; i < n; ++i) {
    s[i] -= '0';
    n_mod = (n_mod * 10 + s[i]) % mod;
  }
  std::reverse(s, s + n);
  std::vector<int64> digits;
  while (n) digits.push_back(div_mod(n, s, b));
  fac[0] = ifac[0] = pw[0] = 1;
  for (int i = 1; i <= m; ++i) {
    fac[i] = fac[i - 1] * i % mod;
    ifac[i] = pow_mod(fac[i], mod - 2);
  }
  for (int i = 1; i <= m * m; ++i) {
    pw[i] = pw[i - 1] * b % mod;
  }
  memset(f, 0, sizeof(f));
  f[0][0][0] = 1;
  for (int i = 1; i <= m; ++i) {
    f[i][0][0] = 1;
    for (int j = 1; j <= i; ++j) {
      for (int k = 0; k <= m; ++k) {
        f[i][j][k] += f[i - 1][j][k];
        for (int t = 0; t <= k; ++t) {
          f[i][j][k] += binom(k, t) * pw[i * t] % mod * f[i - 1][j - 1][k - t] % mod;
        }
        f[i][j][k] %= mod;
      }
    }
  }
  int64 ret = 1;
  for (int i = 0; i < m; ++i) {
    ret = ret * (n_mod + i) % mod;
  }
  for (int size = 1; size <= m; ++size) {
    // get polynomial
    std::vector<int64> a = {1};
    int64 d = (n_mod + m - 1 + (int64)size * (c - 1)) % mod;
    if (d < 0) d += mod;
    for (int i = 0; i < m; ++i) {
      std::vector<int64> t_a(a.size() + 1);
      for (size_t j = 0; j < a.size(); ++j) {
        t_a[j] += a[j] * d % mod;
        t_a[j + 1] += mod - a[j];
      }
      d = (d + mod - 1) % mod;
      a.swap(t_a);
      for (auto &x: a) x %= mod;
    }
    // get base b
    bool negtive = false;
    digits[0] += c - 1;
    if (c - 1 > 0) {
      for (size_t i = 0; i < digits.size(); ++i) {
        int carry = digits[i] / b;
        digits[i] %= b;
        if (!carry) break;
        if (i + 1 == digits.size()) digits.push_back(0);
        digits[i + 1] += carry;
      }
    } else if (c - 1 < 0) {
      for (size_t i = 0; i < digits.size(); ++i) {
        if (digits[i] >= 0) break;
        int carry = 0;
        while (digits[i] < 0) digits[i] += b, ++carry;
        if (i + 1 == digits.size()) negtive = true;
        else digits[i + 1] -= carry;
      }
    }
    if (negtive) break;
    int64 x = 0, y = 0, sum = 0;
    for (int i = digits.size() - 1; i >= 0; --i) if (digits[i] && y <= size) {
      if (i > m) {
        for (int k = 0; k <= m; ++k) sum += f[i - 1][size][k] * a[k] % mod;
        break;
      }
      // to 0
      if (digits[i] > 0) {
        for (int k = 0; k <= m; ++k) {
          int64 p = 1;
          if (!i) {
            if (y == size) {
              for (int t = 0; t < k; ++t) p = p * x % mod;
              sum += a[k] * p % mod;
            }
          } else {
            for (int t = 0; t <= k; ++t) {
              sum += binom(k, t) * p % mod * f[i - 1][size - y][k - t] % mod * a[k] % mod;
              p = p * x % mod;
            }
          }
        }
      }
      // to 1
      if (i && digits[i] > 1 && y + 1 <= size) {
        for (int k = 0; k <= m; ++k) {
          int64 p = 1;
          for (int t = 0; t <= k; ++t) {
            sum += binom(k, t) * p % mod * f[i - 1][size - y - 1][k - t] % mod * a[k] % mod;
            p = p * (x + pw[i]) % mod;
          }
        }
      }
      if (digits[i] > 1) break;
      if (digits[i] == 1) x += pw[i], ++y;
    }
    if (size & 1) ret -= sum % mod;
    else ret += sum % mod;
  }
  ret %= mod; ret += mod; ret %= mod;
  ret = ret * ifac[m] % mod;
  printf("%lld\n", ret);
  return 0;
}

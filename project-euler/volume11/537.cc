#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>

const int mod = 1004535809, g = 3;

using int64 = long long;

int64 pow_mod(int64 a, int64 n) {
  int64 r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % mod;
    a = a * a % mod;
  }
  return r;
}

inline int64 mul_mod(int64 a, int64 b) {
  return a * b % mod;
}

void trans(int64 a[], int n, bool inv = false) {
  int64 w = 1, d = pow_mod(g, (mod - 1) / n), t;
  int i, j, c, s;
  if (inv) {
    for (i = 1, j = n - 1; i < j; std::swap(a[i++], a[j--]));
    for (t = pow_mod(n, mod - 2), i = 0; i < n; ++i) {
      a[i] = mul_mod(a[i], t);
    }
  }
  for (s = n >> 1; s; s >>= w = 1, d = mul_mod(d, d)) {
    for (c = 0; c < s; ++c, w = mul_mod(w, d)) {
      for (i = c; i < n; i += s << 1) {
        t = a[i | s];
        a[i | s] = mul_mod((a[i] + mod - t) % mod, w);
        a[i] = (a[i] + t) % mod;
      }
    }
  }
  for (i = 1; i < n; ++i) {
    for (j = 0, s = i, c = n >> 1; c; c >>= 1, s >>= 1) {
      j = j << 1 | s & 1;
    }
    if (i < j) std::swap(a[i], a[j]);
  }
}

const int N = 1 << 16;

std::vector<int64> conv(const std::vector<int64> &a, const std::vector<int64> &b, int n) {
  int s = 1;
  while (s < n + n - 1) s <<= 1;
  static int64 A[N], B[N];
  for (int i = 0; i < s; ++i) {
    A[i] = i < n ? a[i] : 0;
  }
  trans(A, s);
  if (a.data() == b.data()) {
    for (int i = 0; i < s; ++i) A[i] = A[i] * A[i] % mod;
  } else {
    for (int i = 0; i < s; ++i) {
      B[i] = i < n ? b[i] : 0;
    }
    trans(B, s);
    for (int i = 0; i < s; ++i) A[i] = A[i] * B[i] % mod;
  }
  trans(A, s, true);
  std::vector<int64> res(n);
  for (int i = 0; i < n; ++i) res[i] = A[i];
  return res;
}

int64 T(int n, int k) {
  int m = n * (log(n) + 5);
  std::vector<int> pi(m, 1);
  pi[0] = pi[1] = 0;
  for (int i = 2; i < m; ++i) {
    if (!pi[i]) continue;
    for (int j = i + i; j < m; j += i) {
      pi[j] = 0;
    }
  }
  for (int i = 1; i < m; ++i) pi[i] += pi[i - 1];
  std::vector<int64> c(n + 1);
  for (int i = 1; i < m; ++i) {
    if (pi[i] <= n) c[pi[i]]++;
  }
  std::vector<int64> ret(n + 1, 0);
  ret[0] = 1;
  for (; k; k >>= 1) {
    if (k & 1) ret = conv(ret, c, n + 1);
    c = conv(c, c, n + 1);
  }
  return ret[n];
}

int main() {
  printf("%lld\n", T(3, 3));
  printf("%lld\n", T(10, 10));
  printf("%lld\n", T(1000, 1000));
  printf("%lld\n", T(20000, 20000));
  return 0;
}

#include <bits/stdc++.h>

using LL = long long;

const int M = 20092010;
LL solve(LL n, int m, int a[], int c[]) {
  std::vector<LL> v(m), u(m << 1);
  LL msk = !!n;
  v[0] = 1;
  for (LL i = n; i > 1; i >>= 1) msk <<= 1;
  for (LL x = 0; msk; msk >>= 1, x <<= 1) {
    std::fill(u.begin(), u.end(), 0);
    int b = !!(n & msk);
    x |= b;
    if (x < m) u[x] = 1;
    else {
      for (int i = 0; i < m; ++i) {
        for (int j = 0, t = i + b; j < m; ++j, ++t) {
          u[t] = (u[t] + v[i] * v[j]) % M;
        }
      }
      for (int i = (m << 1) - 1; i >= m; --i) {
        for (int j = 0, t = i - m; j < m; ++j, ++t) {
          u[t] = (u[t] + c[j] * u[i]) % M;
        }
      }
    }
    std::copy(u.begin(), u.begin() + m, v.begin());
  }
  LL ret = 0;
  for (int i = 0; i < m; ++i) {
    ret = (ret + v[i] * a[i]) % M;
  }
  return ret;
}

LL run(LL n) {
  int m = 2000, g[2000], c[2000];
  for (int i = 0; i < 2000; ++i) g[i] = 1;
  memset(c, 0, sizeof(c));
  c[0] = c[1] = 1;
  return solve(n, m, g, c);
}

int main() {
  std::cout << run(1000000000000000000ll) << std::endl;
  return 0;
}


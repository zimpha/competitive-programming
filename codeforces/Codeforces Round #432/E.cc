#include <cstdio>
#include <string>
#include <iostream>
#include <algorithm>

const int mod = 1e9 + 7;

using int64 = long long;

int inv(int x) {
  return x == 1 ? x : int64(mod - mod / x) * inv(mod % x) % mod;
}

void FWT(int a[], int n, bool inv = false) {
  for (int k = 0; (1 << k) < n; ++k) {
    for (int i = 0; i < n; ++i) {
      if (i >> k & 1) continue;
      int j = i ^ (1 << k);
      int y = (a[i] + a[j]) % mod;
      int x = (a[i] - a[j] + mod) % mod;
      if (inv) {
        x = (mod - x) % mod;
        std::swap(x, y);
      }
      a[i] = x, a[j] = y;
    }
  }
}

const int N = 1 << 20;

int a[N], b[N];

int main() {
  int n;
  std::string s;
  std::cin >> n >> s;
  for (int i = 0; i < (1 << n); ++i) {
    a[i] = s[i] - '0';
    b[i] = 1 - a[i];
  }
  FWT(a, 1 << n);
  FWT(b, 1 << n);
  for (int i = 0; i < (1 << n); ++i) {
    a[i] = 1ll * a[i] * b[i] % mod;
  }
  FWT(a, 1 << n, true);
  for (int i = 0; i < (1 << n); ++i) {
    a[i] = 1ll * a[i] * inv(1 << n) % mod;
  }
  int ret = 0;
  for (int i = 0; i < (1 << n); ++i) {
    ret = (ret + 1ll * a[i] * (1 << __builtin_popcount(i))) % mod;
  }
  std::cout << ret * 3ll % mod << std::endl;
  return 0;
}
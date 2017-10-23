#include <cstdio>
#include <cassert>
#include <algorithm>

using int64 = long long;

const int mod = 987654321;

int64 P(int64 n) {
  int64 a = 1, d = 1;
  for (int it = 1; n != 1; ++it) {
    if (it & 1) {
      a += d;
    } else {
      if (n & 1) a += d;
    }
    n /= 2;
    d <<= 1;
  }
  return a;
}

int64 S(int64 n) {
  int64 ret = n % mod;
  for (int64 it = 0; (1ll << it) < n; ++it) {
    int64 d = 1ll << it, m = std::max<int64>(n - d * 2 + 1, 0);
    if (it & 1) {
      if (m == 0) continue;
      // [d, n], it-th bit is 1
      int64 cnt = 0, o = n >> it & 1;
      for (int i = 60; i >= 0; --i) if (i != it) {
        if (n >> i & 1) {
          if (i < it) cnt += o * (1ll << i);
          else cnt += 1ll << (i - 1);
        }
      }
      cnt += o;
      cnt -= 1ll << (it);
      ret += (cnt % mod) * (d % mod) % mod;
    } else ret += (m % mod) * (d % mod) % mod;
    ret %= mod;
  }
  return ret;
}

int main() {
  printf("%lld\n", S(1000));
  printf("%lld\n", S(1000000000000000000ll));
  return 0;
}

#include <cstdio>
#include <cstring>
#include <bitset>
#include <algorithm>

using state = std::bitset<1025>;
const int N = 2000 + 10;

char s[N];

int gcd(int a, int b) {
  return b ? gcd(b, a % b) : a;
}

int count(int n, bool ignore) {
  int ret = 0;
  for (int k = 0; k <= n / 2; ++k) {
    if (k * 2 == n && ignore) continue;
    int g = gcd(n, k), nn = n / g, kk = k / g;
    state one;
    for (int i = 0; i < nn; ++i) one[i] = 1;
    state b0 = one, b1;
    for (int i = 0; i < kk; ++i) {
      b0[i * nn / kk] = 0;
      b1[i * nn / kk] = 1;
    }
    for (int i = 0; i < n; ++i) {
      if (s[i] == '0') one &= b0;
      else if (s[i] == '1') one &= b1;
      int v0 = b0[0], v1 = b1[0];
      b0 >>= 1; b1 >>= 1;
      b0[nn - 1] = v0; b1[nn - 1] = v1;
    }
    ret += one.count();
  }
  return ret;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    scanf("%s", s);
    int n = strlen(s);
    int ret = count(n, false);
    for (int i = 0; i < n; ++i) {
      if (s[i] != '?') s[i] = '0' + '1' - s[i];
    }
    ret += count(n, true);
    printf("%d\n", ret);
  }
  return 0;
}

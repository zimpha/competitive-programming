#include <cstdio>

using int64 = long long;

// ax + by = gcd(a, b), |x| + |y| is minimum
void exgcd(int64 a, int64 b, int64 &g, int64 &x, int64 &y) {
  if (!b) x = 1, y = 0, g = a;
  else {
    exgcd(b, a % b, g, y, x);
    y -= x * (a / b);
  }
}

int64 crt(int n, int64 *c, int64 *m) {
  int64 M = 1, ans = 0;
  for (int i = 0; i < n; ++i) M *= m[i];
  for (int i = 0; i < n; ++i) {
    int64 x, y, g, tm = M / m[i];
    exgcd(tm, m[i], g, x, y);
    ans = (ans + tm * x * c[i] % M) % M;
  }
  return (ans + M) % M;
}

int main() {
  int T, n, m;
  scanf("%d%d%d", &T, &n, &m);
  for (int cas = 1; cas <= T; ++cas) {
    int64 m[7] = {4, 3, 5, 7, 11, 13, 17};
    int64 c[7];
    for (int i = 0; i < 7; ++i) {
      for (int j = 0; j < 18; ++j) {
        printf("%lld ", m[i]);
      }
      puts("");
      fflush(stdout);
      c[i] = 0;
      for (int j = 0; j < 18; ++j) {
        int x;
        scanf("%d", &x);
        c[i] = (c[i] + x) % m[i];
      }
    }
    int64 ret = crt(7, c, m);
    printf("%lld\n", ret);
    fflush(stdout);
    scanf("%lld", &ret);
  }
  return 0;
}

#include <cstdio>
#include <cassert>

using int64 = long long;

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    int64 bound = 1;
    for (int i = 0; i < n; ++i) bound *= 10;
    int64 a, b, c, d;
    scanf("%lld", &a);
    int64 s = bound * 2;
    printf("%lld\n", s + a);
    fflush(stdout);
    scanf("%lld", &b);
    s -= b;
    c = s - bound;
    printf("%lld\n", c);
    fflush(stdout);
    s -= c;
    scanf("%lld", &d);
    printf("%lld\n", s - d);
    fflush(stdout);
    int res;
    scanf("%d", &res);
    assert(res == 1);
  }
  return 0;
}

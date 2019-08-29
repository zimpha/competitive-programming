#include <cstdio>

using int64 = long long;

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int64 n, k, r;
    scanf("%lld%lld%lld", &n, &k, &r);
    if (k == 1) {
      printf("%lld\n", (r - 1) % n + 1);
      continue;
    }
    int64 s = 1, c = n, e = n;
    for (int64 w = 1; ; w *= k) {
      auto a = (c - 1) / k;
      auto v = (c - 1) % k;
      if (a >= r) {
        printf("%lld\n", (s + (r - 1) * w * k + s + r * w * k - 1) * k * w / 2);
        break;
      } else {
        auto ss = s + w * a * k;
        r -= a;
        if (v + 1 == k) {
          c = a + 1;
          e += (ss + ss + v * w - 1) * v * w / 2;
          --r;
          if (r == 0) {
            printf("%lld\n", e);
            break;
          }
        } else {
          if (v + 1 + a <= k) {
            printf("%lld\n", n * (n + 1) / 2);
            break;
          } else {
            auto t = k - v - 1;
            --r;
            e += (ss + ss + v * w - 1) * v * w / 2;
            e += (s + s + t * k * w - 1) * t * k * w / 2;
            if (r == 0) {
              printf("%lld\n", e);
              break;
            }
            c = a - (k - v - 1) + 1;
            s = s + k * w * t;
          }
        }
      }
    }
  }
  return 0;
}

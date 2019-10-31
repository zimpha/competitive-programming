#include <cstdio>

using int64 = long long;

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int64 l, r, k;
    scanf("%lld%lld%lld", &l, &r, &k);
    if (k & 1) printf("%lld\n", r - l + 1);
    else {
      auto sum = [] (int64 n, int64 k) {
        if (n < k) return n + 1;
        int64 l = n / k;
        int64 zeros = l / (k + 1) * k;
        if (l % (k + 1)) {
          zeros += l % (k + 1) - 1;
          zeros += n % k >= l % (k + 1) - 1;
        }
        return n + 1 - zeros;
      };
      printf("%lld\n", sum(r, k) - sum(l - 1, k));
    }
  }
  return 0;
}

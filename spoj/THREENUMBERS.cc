#include <cstdio>

using int64 = long long;

int gcd(int a, int b) {
  return b ? gcd(b, a % b) : a;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int a, b, n;
    scanf("%d%d%d", &a, &b, &n);
    int ab = a * b / gcd(a, b);
    int64 left = 0, right = (int64)n * a;
    while (left < right) {
      int64 mid = (left + right - 1) >> 1;
      int64 cnt = mid / a + mid / b - mid / ab;
      if (cnt >= n) right = mid;
      else left = mid + 1;
    }
    printf("%lld\n", left);
  }
  return 0;
}

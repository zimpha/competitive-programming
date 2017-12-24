#include <cstdio>
#include <vector>

using int64 = long long;

int gcd(int a, int b) {
  return b ? gcd(b, a % b) : a;
}

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> a(n), l(n), val(n);
  int64 ret = 0;
  for (int i = 0, x; i < n; ++i) {
    scanf("%d", &a[i]);
    l[i] = i; val[i] = a[i];
    for (int cur = i; cur >= 0; cur = l[cur] - 1) {
      val[cur] = gcd(val[cur], a[i]);
      while (l[cur] - 1 >= 0 && gcd(a[i], val[l[cur] - 1]) == gcd(a[i], val[cur])) {
        l[cur] = l[l[cur] - 1];
      }
      ret += (int64)val[cur] * (cur - l[cur] + 1);
    }
  }
  printf("%lld\n", ret);
  return 0;
}

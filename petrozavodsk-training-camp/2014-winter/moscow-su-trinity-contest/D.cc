#include <cstdio>
#include <cmath>

int main() {
  int n, k;
  scanf("%d%d", &n, &k);
  if (k == 1) printf("%lld\n", 1ll * n * (n + 1) / 2);
  else {
    double ret = 0;
    for (int i = 1; i <= n && i <= 1000000; ++i) {
      ret += pow(k, (i + 1) / 2 - i) * (n - i + 1);
    }
    printf("%.10f\n", ret);
  }
  return 0;
}

#include <cstdio>
#include <vector>
#include <algorithm>

using int64 = long long;

void exgcd(int64 a, int64 b, int64 &g, int64 &x, int64 &y) {
  if (!b) x = 1, y = 0, g = a;
  else {
    exgcd(b, a % b, g, y, x);
    y -= x * (a / b);
  }
}

int main() {
  int n, p, b;
  scanf("%d%d%d", &n, &p, &b);
  std::vector<int64> a(n + 1), x(n + 1), y(n + 1);
  for (int i = 0; i < n; ++i) {
    scanf("%lld", &a[i]);
    a[i] %= p;
  }
  if (*std::max_element(a.begin(), a.end()) == 0) {
    if (b) puts("NO");
    else {
      puts("YES");
      for (int i = 0; i < n; ++i) printf("0 ");
      puts("");
    }
    return 0;
  }
  a[n] = p;
  int64 g = a[0];
  for (int i = 0; i < n; ++i) {
    exgcd(g, a[i + 1], g, x[i], y[i]);
  }
  if (b % g) puts("NO");
  else {
    puts("YES");
    g = b / g;
    for (int i = n - 1; i >= 0; --i) {
      g = (g * x[i] % p + p) % p;
      x[i] = (g * (i ? y[i - 1] : 1) % p + p) % p;
    }
    for (int i = 0; i < n; ++i) {
      printf("%lld ", x[i]);
    }
    puts("");
  }
  return 0;
}

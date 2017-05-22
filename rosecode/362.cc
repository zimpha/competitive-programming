#include <bits/stdc++.h>

int fac[100], cnt[100], m;
long count, sx, sy;

void dfs(int d, long x, long y, long n) {
  if (d == m) {
    if (y >= x) {
      count++;
      sx += x + n;
      sy += y + n;
    }
    return;
  }
  for (int i = 0; i <= cnt[d]; ++i) {
    dfs(d + 1, x, y, n);
    x *= fac[d];
    y /= fac[d];
  }
}

void run(long n) {
  m = 0;
  long cache = n;
  for (int i = 2; i * i <= n; ++i) if (n % i == 0) {
    fac[m++] = i;
    cnt[m - 1] = 0;
    while (n % i == 0) cnt[m - 1] += 2, n /= i;
  }
  if (n > 1) fac[m] = n, cnt[m++] = 2;
  n = cache;
  count = sx = sy = 0;
  dfs(0, 1, n * n, n);
  std::cout << count << ',' << sx << ',' << sy << std::endl;
}

int main() {
  run(12345ll);
  run(2091129587ll);
  return 0;
}

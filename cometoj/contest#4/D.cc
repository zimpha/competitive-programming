#include <cstdio>
#include <cstring>
#include <algorithm>

using uint64 = unsigned long long;

int f(uint64 m) {
  static int s[100], t[100];
  int n = 0;
  for (; m; m /= 10) s[n++] = m % 10;
  std::reverse(s, s + n);
  while (n != 1) {
    int m = 0;
    for (int i = 1; i < n; ++i) {
      int c = (s[i] + s[i - 1]) % 10;
      if (m == 0 && c == 0) continue;
      t[m++] = c;
    }
    if (!m) t[m++] = 0;
    n = m;
    for (int i = 0; i < n; ++i) s[i] = t[i];
  }
  return s[0];
}

uint64 solve(uint64 n) {
  if (n < 10) return (n + 1) * n / 2;
  uint64 s = n / 10 * 45;
  int o = n % 10, t = f(n / 10 * 10);
  for (int i = 0; i <= o; ++i) {
    s += (t + i) % 10;
  }
  return s;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    uint64 l, r;
    scanf("%llu%llu", &l, &r);
    printf("%llu\n", solve(r) - solve(l - 1));
  }
  return 0;
}

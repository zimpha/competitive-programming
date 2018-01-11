#include <cstdio>
#include <set>

int main() {
  std::set<int> fib = {0, 1};
  int a = 0, b = 1;
  while (a < 100000000) {
    int c = a + b;
    fib.insert(c);
    a = b;
    b = c;
  }
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, m;
    scanf("%d%d", &n, &m);
    int s = 1 % m;
    for (int i = 2; i * i <= n; ++i) {
      if (n % i == 0) {
        s += i % m;
        if (i * i != n) s += n / i % m;
        s %= m;
      }
    }
    int cnt = 1;
    for (int i = 2; i * i <= s; ++i) {
      if (s % i == 0) {
        ++cnt;
        if (i * i != s) ++cnt;
      }
    }
    printf("Case #%d : %s.\n", cas, fib.count(cnt) ? "YES" : "NO");
  }
  return 0;
}

#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>
#include <string>
#include <algorithm>

const int N = 2e5 + 10;

char s[N];

int main() {
  int n, k, m;
  scanf("%d%d%s", &k, &m, s);
  scanf("%d", &n);
  std::vector<int> a(n), b(n), c(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d%d%d", &a[i], &b[i], &c[i]);
  }
  for (int i = 0; i < k; ++i) {
    int p = i;
    for (int j = n - 1; j >= 0; --j) {
      int x = c[j], y = x + b[j] - a[j];
      if (p >= y) p -= b[j] - a[j];
      else if (p >= x) p = a[j] + p - x;
    }
    putchar(s[p]);
  }
  puts("");
  return 0;
}

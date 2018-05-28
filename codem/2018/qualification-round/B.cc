#include <cstdio>
#include <vector>
#include <algorithm>

int main() {
  int n, m, k;
  scanf("%d%d%d", &n, &m, &k);
  int mx = 0, pos = -1;
  for (int i = 0; i < k; ++i) {
    int a, b;
    scanf("%d%d", &a, &b);
    if (pos == -1 || b * (n - m) + a * m >= mx) {
      mx = b * (n - m) + a * m;
      pos = i;
    }
  }
  std::vector<int> ret(k);
  ret[pos] = n;
  for (int i = 0; i < k; ++i) {
    if (i) putchar(' ');
    printf("%d", ret[i]);
  }
  puts("");
  return 0;
}

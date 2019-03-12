#include <cstdio>
#include <vector>
#include <algorithm>

const int N = 1e6 + 10;

int a[N];

int main() {
  int n = 0;
  for (int x; scanf("%d", &x) == 1 && x; ) {
    a[n++] = x;
    if (n > 1000) break;
  }
  std::sort(a, a + n);
  for (int i = 0; i + 2 < n; ++i) {
    if (a[i] + a[i + 1] > a[i + 2]) {
      printf("%d %d %d\n", a[i], a[i + 1], a[i + 2]);
      return 0;
    }
  }
  puts("NIE");
  return 0;
}

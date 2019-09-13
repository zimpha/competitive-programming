#include <cstdio>
#include <algorithm>

const int N = 1e6 + 10;

char s[N];

int main() {
  int n, m;
  scanf("%d%d", &m, &n);
  scanf("%s", s);
  n *= 2;
  for (int i = 1; i < m; ) {
    if (s[i] != s[i - 1]) {
      s[i] = s[i - 1] = 0;
      i += 2;
      n -= 2;
    } else {
      ++i;
    }
  }
  if (s[m - 1]) --n;
  printf("%d\n", std::max(0, n));
  return 0;
}

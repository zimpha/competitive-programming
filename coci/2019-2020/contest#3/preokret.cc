#include <cstdio>
#include <algorithm>

int main() {
  int n;
  scanf("%d", &n);
  int c1 = 0, c2 = 0;
  int tie = 1;
  int mx = 0, last = -1, cnt = 0;
  for (int i = 0; i < n; ++i) {
    int x;
    scanf("%d", &x);
    if (x == last) ++cnt;
    else last = x, cnt = 1;
    if (x == 1) ++c1;
    else ++c2;
    if (c1 == c2) ++tie;
    if (x == 1) {
      if (c1 > c2 && c1 - cnt < c2) mx = std::max(mx, cnt);
    } else {
      if (c1 < c2 && c1 > c2 - cnt) mx = std::max(mx, cnt);
    }
  }
  printf("%d %d\n%d\n%d\n", c1, c2, tie, mx);
  return 0;
}

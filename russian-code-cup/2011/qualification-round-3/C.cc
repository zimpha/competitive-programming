#include <cstdio>
#include <algorithm>

int main() {
  int hh, mm;
  scanf("%d:%d", &hh, &mm);
  int now = hh * 60 + mm;
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    int h1, m1, h2, m2, t;
    scanf("%d:%d %d:%d %d", &h1, &m1, &h2, &m2, &t);
    int l = h1 * 60 + m1, r = h2 * 60 + m2 - t;
    now = std::max(now, l);
    if (now > r) {
      puts("No");
      return 0;
    }
    now += t;
  }
  if (now > 1440) {
    puts("No");
  } else {
    puts("Yes");
    printf("%02d:%02d\n", now / 60, now % 60);
  }
  return 0;
}

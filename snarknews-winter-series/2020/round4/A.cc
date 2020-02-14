#include <cstdio>
#include <cstring>
#include <algorithm>

int cnt[20][20];

void inc(int x, int y) {
  if (x < 0 || y < 0 || x > 10 || y > 10) return;
  int l = 0, r = 10;
  if (y > 5) l += y - 5, r -= y - 5;
  if (x < l || x > r) return;
  cnt[x][y]++;
}

void go(int x, int y) {
  for (int i = 0; i < 11; ++i) {
    if (i != y) inc(x, i);
  }
  if (x <= 5) {
    for (int i = 0; i <= 5; ++i) {
      if (i != x) inc(i, y);
      if (i != x) inc(i, y + (i - x));
    }
    for (int i = 6; i < 11; ++i) {
      inc(i, y - (i - 5));
      inc(i, y + (5 - x));
    }
  } else {
    for (int i = 5; i < 11; ++i) {
      if (i != x) inc(i, y);
      if (i != x) inc(i, y + (x - i));
    }
    for (int i = 0; i < 5; ++i) {
      inc(i, y + (x - 5));
      inc(i, y - (5 - i));
    }
  }
}

int main() {
  char s[10], t[20];
  scanf("%s%s", s, t);
  int x1 = s[0] - 'a', y1 = std::atoi(s + 1) - 1;
  int x2 = t[0] - 'a', y2 = std::atoi(t + 1) - 1;
  go(x1, y1);
  go(x2, y2);
  int ret = 0;
  for (int i = 0; i < 11; ++i) {
    for (int j = 0; j < 11; ++j) {
      ret += cnt[i][j] == 2;
    }
  }
  printf("%d\n", ret);
  return 0;
}

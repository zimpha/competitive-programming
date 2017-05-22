#include <cmath>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <iostream>
#include <algorithm>

int n, nn, m;

bool ask(int x) {
  if (x + 1 > n) return true;
  printf("? %d\n", x + 1);
  fflush(stdout);
  static char res[5];
  scanf("%s", res);
  return res[0] == '<';
}

int intersect(int a, int b, int c, int d) {
  int l = std::max(a, c), r = std::min(b, d);
  return l <= r ? r - l + 1 : 0;
}

int count(int l, int r, int st, int len) {
  int total = r - l + 1;
  if (st + len - 1 < nn) total -= intersect(l, r, st, st + len - 1) / 2;
  else total -= intersect(l, r, st, nn - 1) / 2 + intersect(l, r, 0, st + len - nn - 1) / 2;
  return total;
}

int get_mid(int l, int r, int st, int len) {
  int left = l, right = r;
  while (left < right) {
    int mid = (left + right) >> 1;
    if (count(l, mid, st, len) < count(mid + 1, r, st, len)) left = mid + 1;
    else right = mid;
  }
  return left;
}

int main() {
  srand(time(NULL));
  scanf("%d%d", &n, &m);
  nn = n + (n & 1);
  int x = 0;
  while ((1 << (x + 1)) <= nn) ++x;
  int a = 1 << x, b = (nn - a) * 2;
  for (int i = 0; i < m; ++i) {
    int st = rand() % (nn / 2) * 2;
    int l = 0, r = nn - 1;
    while (l < r) {
      int mid = get_mid(l, r, st, b);
      if (ask(mid + 1)) r = mid;
      else l = mid + 1;
    }
    printf("= %d\n", l + 1);
    fflush(stdout);
  }
  return 0;
}

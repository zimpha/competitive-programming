#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>

void u(int x, int y, int trans) {
  if (trans) printf("%d %d\n", y, x);
  else printf("%d %d\n", x, y);
}

void construct(int sx, int sy, int n, int m, int trans) {
  if (n == 4 && m == 4) {
    for (int y : std::vector<int>{0}) {
      for (int x = 0; x < 4; ++x) {
        u(sx + x + 1, sy + y + 1, trans);
        if (x & 1) y -= 2;
        else y += 2;
      }
    }
    for (int y : std::vector<int>{3}) {
      for (int x = 0; x < 4; ++x) {
        u(sx + x + 1, sy + y + 1, trans);
        if (x & 1) y += 2;
        else y -= 2;
      }
    }
    for (int y : std::vector<int>{2}) {
      for (int x = 0; x < 4; ++x) {
        u(sx + x + 1, sy + y + 1, trans);
        if (x & 1) y += 2;
        else y -= 2;
      }
    }
    for (int y : std::vector<int>{1}) {
      for (int x = 0; x < 4; ++x) {
        u(sx + x + 1, sy + y + 1, trans);
        if (x & 1) y -= 2;
        else y += 2;
      }
    }
    return;
  }
  if (n == 3 && m == 4) {
    u(sx + 1, sy + 1, trans);
    u(sx + 3, sy + 2, trans);
    u(sx + 1, sy + 3, trans);
    u(sx + 3, sy + 4, trans);
    u(sx + 2, sy + 2, trans);
    u(sx + 1, sy + 4, trans);
    u(sx + 2, sy + 1, trans);
    u(sx + 3, sy + 3, trans);
    u(sx + 1, sy + 2, trans);
    u(sx + 2, sy + 4, trans);
    u(sx + 3, sy + 1, trans);
    u(sx + 2, sy + 3, trans);
    return;
  }
  if (n == 3) {
    for (int i = 0; i + 3 < m; ++i) {
      u(sx + 1, sy + 1 + i, trans);
      u(sx + 3, sy + 1 + i + 1, trans);
      u(sx + 2, sy + 1 + i + 3, trans);
    }
    u(sx + 3, sy + 1, trans);
    u(sx + 1, sy + 1 + m - 1, trans);
    u(sx + 2, sy + 1 + 2, trans);
    for (int i = 0; i < 2; ++i) {
      u(sx + 3, sy + 1 + m - 1 - i, trans);
      u(sx + 1, sy + 1 + m - 2 - i, trans);
      u(sx + 2, sy + 1 + 1 - i, trans);
    }
  } else {
    for (int i = 0; i + 3 < m; ++i) {
      u(sx + 1, sy + 1 + i, trans);
      u(sx + 2, sy + 1 + i + 3, trans);
    }
    for (int i = m - 3; i < m; ++i) {
      u(sx + 1, sy + 1 + i, trans);
      u(sx + 2, sy + 1 + (i - m + 3), trans);
    }
  }
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, m, trans = 0;
    scanf("%d%d", &n, &m);
    if (n > m) std::swap(n, m), trans = 1;
    if (n == 2 && m <= 4) printf("Case #%d: IMPOSSIBLE\n", cas);
    else if (n == 3 && m == 3) printf("Case #%d: IMPOSSIBLE\n", cas);
    else {
      printf("Case #%d: POSSIBLE\n", cas);
      if (n == 4 && m == 4) construct(0, 0, 4, 4, trans);
      else {
        if (n % 2 == 0) {
          for (int i = 0; i < n; i += 2) construct(i, 0, 2, m, trans);
        } else {
          for (int i = 0; i < n - 3; i += 2) construct(i, 0, 2, m, trans);
          construct(n - 3, 0, 3, m, trans);
        }
      }
    }
  }
  return 0;
}

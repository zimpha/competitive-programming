#include <cstdio>
#include <bitset>
#include <cassert>
#include <cstring>
#include <vector>
#include <algorithm>

using uint64 = unsigned long long;

const int N = 1024, M = 210;

char paper[N][N], stamp[M][M];
uint64 eq[N * 2][32];
int sp[N][2], ss[N][2];

int get(uint64 *u, int x) {
  return u[x / 64] >> (x % 64) & 1;
}

void set(uint64 *u, int x, int y) {
  assert(get(u, x) == 0);
  u[x / 64] ^= uint64(y) << (x % 64);
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, m, delta;
    scanf("%d%d", &m, &n);
    int x1 = -1, x2, y1, y2;
    for (int i = 0; i < 3; ++i) {
      char s[10];
      scanf("%s", s);
      for (int j = 0; j < 3; ++j) if (s[j] == '1') {
        if (x1 == -1) x1 = i, y1 = j;
        else x2 = i, y2 = j;
      }
    }
    for (int i = 0; i < m; ++i) scanf("%s", stamp[i]);
    for (int i = 0; i < n; ++i) scanf("%s", paper[i]);
    if (y1 == y2) {
      for (int i = 0; i < n / 2; ++i) {
        for (int j = i; j < n - 1 - i; ++j) {
          char t = paper[j][i];
          paper[j][i] = paper[n - 1 - i][j];
          paper[n - 1 - i][j] = paper[n - 1 - j][n - 1 - i];
          paper[n - 1 - j][n - 1 - i] = paper[i][n - 1 - j];
          paper[i][n - 1 - j] = t;
        }
      }
      for (int i = 0; i < m / 2; ++i) {
        for (int j = i; j < m - 1 - i; ++j) {
          char t = stamp[j][i];
          stamp[j][i] = stamp[m - 1 - i][j];
          stamp[m - 1 - i][j] = stamp[m - 1 - j][m - 1 - i];
          stamp[m - 1 - j][m - 1 - i] = stamp[i][m - 1 - j];
          stamp[i][m - 1 - j] = t;
        }
      }
      delta = x2 - x1;
    } else {
      delta = y2 - y1;
    }
    for (int i = 0; i < m; ++i) {
      //puts(stamp[i]);
    }
    for (int i = 0; i < n; ++i) {
      //puts(paper[i]);
    }
    int x, y;
    memset(sp, 0, sizeof(sp));
    memset(ss, 0, sizeof(ss));
    memset(eq, 0, sizeof(eq));
    if (delta == 1) {
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
          sp[i][0] ^= paper[i][j] == '1';
        }
      }
      for (int i = 0; i < m; ++i) {
        for (int j = 0; j < m; ++j) {
          ss[i][0] ^= stamp[i][j] == '1';
        }
      }
      for (int i = 0; i < n; ++i) {
        set(eq[i], n - m + 1, sp[i][0]);
        for (int j = std::max(0, i - m + 1); j <= i && j + m <= n; ++j) {
          set(eq[i], j, ss[i - j][0]);
        }
      }
      x = n, y = n - m + 1;
    } else {
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
          sp[i][j & 1] ^= paper[i][j] == '1';
        }
      }
      for (int i = 0; i < m; ++i) {
        for (int j = 0; j < m; ++j) {
          ss[i][j & 1] ^= stamp[i][j] == '1';
        }
      }
      for (int i = 0; i < n; ++i) {
        set(eq[i], 2 * (n - m + 1), sp[i][0]);
        set(eq[i + n], 2 * (n - m + 1), sp[i][1]);
        for (int j = std::max(0, i - m + 1); j <= i && j + m <= n; ++j) {
          set(eq[i], j, ss[i - j][0]);
          set(eq[i + n], j, ss[i - j][1]);
          if (n != m) {
            set(eq[i], j + n - m + 1, ss[i - j][1]);
            set(eq[i + n], j + n - m + 1, ss[i - j][0]);
          }
        }
      }
      x = n * 2, y = (n - m + 1) * 2;
    }
    bool valid = true;
    int bound = y / 64 + 1;
    for (int i = 0; i < x && i < y; ++i) {
      int r = -1;
      for (int j = i; j < x; ++j) {
        if (get(eq[j], i))r = j;
      }
      if (r == -1) continue;
      if (r != i) {
        for (int k = 0; k < bound; ++k) {
          std::swap(eq[r][k], eq[i][k]);
        }
      }
      for (int j = 0; j < x; ++j) if (get(eq[j], i) && j != i) {
        int k = 0;
        for (k = 0; k + 3 < bound; k += 4) {
          eq[j][k] ^= eq[i][k];
          eq[j][k + 1] ^= eq[i][k + 1];
          eq[j][k + 2] ^= eq[i][k + 2];
          eq[j][k + 3] ^= eq[i][k + 3];
        }
        for (; k < bound; ++k) eq[j][k] ^= eq[i][k];
      }
    }
    for (int i = 0; i < x; ++i) {
      if (i < y) {
        valid &= get(eq[i], i) || !get(eq[i], y);
      } else {
        valid &= !get(eq[i], y);
      }
    }
    puts(valid ? "TAK" : "NIE");
  }
  return 0;
}

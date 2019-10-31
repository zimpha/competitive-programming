#include <cstdio>
#include <bitset>
#include <cassert>
#include <cstring>
#include <vector>
#include <algorithm>

using uint64 = unsigned long long;

const int N = 1024;

char s[N * N];
uint64 eq[N * 2][32];
int sum[N][2];

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
    int n, m, r, c;
    scanf("%d%d%d%d", &n, &m, &r, &c);
    if (n < m) {
      memset(sum, 0, sizeof(sum[0]) * n);
      for (int i = 0; i < n; ++i) {
        scanf("%s", s);
        for (int j = 0; j < m; ++j) {
          sum[i][j & 1] ^= s[j] - '0';
        }
      }
      for (int i = 0; i < n; ++i) {
        scanf("%s", s);
        for (int j = 0; j < m; ++j) {
          sum[i][j & 1] ^= s[j] - '0';
        }
      }
    } else {
      memset(sum, 0, sizeof(sum[0]) * m);
      for (int i = 0; i < n; ++i) {
        scanf("%s", s);
        for (int j = 0; j < m; ++j) {
          sum[j][i & 1] ^= s[j] - '0';
        }
      }
      for (int i = 0; i < n; ++i) {
        scanf("%s", s);
        for (int j = 0; j < m; ++j) {
          sum[j][i & 1] ^= s[j] - '0';
        }
      }
      std::swap(n, m); std::swap(r, c);
    }
    memset(eq, 0, sizeof(eq[0]) * (n * 2 + 1));
    int x = n, y = n;
    if (c == 1) {
      int s[3] = {0, 0, 0};
      if (r == 1) s[0] = s[1] = 1;
      else s[0] = s[2] = 1;
      for (int i = 0; i < n; ++i) {
        set(eq[i], n, sum[i][0] ^ sum[i][1]);
        for (int j = std::max(0, i - r); j <= i && j + r < n; ++j) {
          set(eq[i], j, s[i - j]);
        }
      }
    } else {
      int s[3] = {0, 0, 0};
      if (r == 1) s[0] = s[1] = 1;
      else s[0] = s[2] = 1;
      for (int i = 0; i < n; ++i) {
        set(eq[i], 2 * n, sum[i][0]);
        set(eq[i + n], 2 * n, sum[i][1]);
        for (int j = std::max(0, i - r); j <= i && j + r < n; ++j) {
          set(eq[i], j, s[i - j]);
          if (m > 1) {
            set(eq[i + n], j + n, s[i - j]);
          }
        }
      }
      x = n * 2, y = n * 2;
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
    puts(valid ? "Yes" : "No");
  }
  return 0;
}

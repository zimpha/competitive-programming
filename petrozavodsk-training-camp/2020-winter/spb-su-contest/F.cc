#include <cstdio>
#include <cassert>
#include <vector>
#include <set>

using uint64 = unsigned long long;

const int N = 2000 + 10;

int sg[N][N];

struct Bitset {
  uint64 u[100];
  void set(uint64 x) { u[x / 64] |= uint64(1) << (x % 64); }
} row[N], col[N], dia[N];

void prepare() {
  row[0].set(0); col[0].set(0); dia[0].set(0);
  for (int s = 1; s < N * 2; ++s) {
    for (int i = 0; i < N && i <= s; ++i) {
      int j = s - i;
      if (j < 0 || j >= N || i > j) continue;
      int m = (3 * std::max(i, j) + 5 + 63) / 64;
      if (m > 99) m = 99;
      int x = -1, y = -1;
      if (i >= 1 && j >= 2) x = sg[i - 1][j - 2];
      if (i >= 2 && j >= 1) y = sg[i - 2][j - 1];
      bool found = false;
      for (int k = 0; k <= m && !found; ++k) if (~(row[i].u[k] | col[j].u[k] | dia[j - i].u[k])) {
        auto w = ~(row[i].u[k] | col[j].u[k] | dia[j - i].u[k]);
        while (w) {
          int t = __builtin_ctzll(w);
          w ^= uint64(1) << t;
          t += k * 64;
          if (t != x && t != y) {
            sg[i][j] = sg[j][i] = t;
            found = true;
            break;
          }
        }
      }
      row[i].set(sg[i][j]); col[j].set(sg[i][j]);
      row[j].set(sg[i][j]); col[i].set(sg[i][j]);
      dia[j - i].set(sg[i][j]);
    }
  }
}

int main() {
  prepare();
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    std::vector<int> r(n), c(n);
    for (int i = 0; i < n; ++i) {
      scanf("%d%d", &r[i], &c[i]);
      --r[i], --c[i];
    }
    int sum = 0;
    for (int i = 0; i < n; ++i) sum ^= sg[r[i]][c[i]];
    if (sum == 0) puts("-1 -1 -1");
    else {
      bool found = false;
      for (int i = 0; i < n && !found; ++i) {
        sum ^= sg[r[i]][c[i]];
        int x = N, y = N;
        auto upd = [&](int a, int b) {
          found = true;
          if (a < x || (a == x && b < y)) x = a, y = b;
        };

        for (int k = 0; k < r[i]; ++k) if (!(sum ^ sg[k][c[i]])) {
          upd(k, c[i]);
        }
        for (int k = 0; k < c[i]; ++k) if (!(sum ^ sg[r[i]][k])) {
          upd(r[i], k);
        }
        for (int k = 1; k <= r[i] && k <= c[i]; ++k) if (!(sum ^ sg[r[i] - k][c[i] - k])) {
          upd(r[i] - k, c[i] - k);
        }
        if (r[i] >= 1 && c[i] >= 2 && !(sum ^ sg[r[i] - 1][c[i] - 2])) upd(r[i] - 1, c[i] - 2);
        if (r[i] >= 2 && c[i] >= 1 && !(sum ^ sg[r[i] - 2][c[i] - 1])) upd(r[i] - 2, c[i] - 1);
        if (found) {
          printf("%d %d %d\n", i + 1, x + 1, y + 1);
        }
        sum ^= sg[r[i]][c[i]];
      }
    }
  }
  return 0;
}

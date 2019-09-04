#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using int64 = long long;
const int N = 200000 + 10;

int idx[N];
int64 ret[N];
int x[N], y[N];
int64 xy[N];
char type[N];

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) {
    idx[i] = i;
    scanf(" %c%d%d", &type[i], &x[i], &y[i]);
    --x[i], --y[i];
    xy[i] = (int64)x[i] * m + y[i];
  }
  std::sort(xy, xy + n);

  auto find = [&](int x, int y) {
    auto key = (int64)x * m + y;
    auto i = std::lower_bound(xy, xy + n, key) - xy;
    return i < n && xy[i] == key;
  };

  for (int i = 0; i < n; ++i) {
    if (type[i] == 'K') {
      for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
          if (!dx && !dy) continue;
          int xx = x[i] + dx, yy = y[i] + dy;
          if (xx >= 0 && xx < m && yy >= 0 && yy < m) {
            ret[i] += !find(xx, yy);
          }
        }
      }
    } else if (type[i] == 'S') {
      static const int dx[8] = {-2, -2, -1, -1, 1, 1, 2, 2};
      static const int dy[8] = {-1, 1, -2, 2, -2, 2, -1, 1};
      for (int k = 0; k < 8; ++k) {
        int xx = x[i] + dx[k], yy = y[i] + dy[k];
        if (xx >= 0 && xx < m && yy >= 0 && yy < m) {
          ret[i] += !find(xx, yy);
        }
      }
    }
  }

  auto solve = [&] () {
    std::sort(idx, idx + n, [&](int a, int b) {
      return x[a] < x[b] || (x[a] == x[b] && y[a] < y[b]);
    });
    for (int i = 0, j; i < n; i = j) {
      int xi = x[idx[i]], prev = -1;
      for (j = i; j < n; ++j) {
        int pj = idx[j];
        if (xi != x[pj]) break;
        if (type[pj] == 'H' || type[pj] == 'W') {
          ret[pj] += prev == -1 ? y[pj] : y[pj] - y[prev] - 1;
        }
        if (prev != -1 && (type[prev] == 'H' || type[prev] == 'W')) {
          ret[prev] += y[pj] - y[prev] - 1;
        }
        prev = pj;
      }
      if (type[prev] == 'H' || type[prev] == 'W') {
        ret[prev] += m - 1 - y[prev];
      }
    }

    std::sort(idx, idx + n, [&](int a, int b) {
      return x[a] + y[a] < x[b] + y[b] || (x[a] + y[a] == x[b] + y[b] && x[a] < x[b]);
    });
    for (int i = 0, j; i < n; i = j) {
      int xyi = x[idx[i]] + y[idx[i]], prev = -1;
      int xl = std::max(0, xyi - (m - 1));
      int xr = std::min(m - 1, xyi);
      for (j = i; j < n; ++j) {
        int pj = idx[j];
        if (xyi != x[pj] + y[pj]) break;
        if (type[pj] == 'H' || type[pj] == 'G') {
          ret[pj] += prev == -1 ? x[pj] - xl : x[pj] - x[prev] - 1;
        }
        if (prev != -1 && (type[prev] == 'H' || type[prev] == 'G')) {
          ret[prev] += x[pj] - x[prev] - 1;
        }
        prev = pj;
      }
      if (type[prev] == 'H' || type[prev] == 'G') {
        ret[prev] += xr - x[prev];
      }
    }
  };

  solve();
  // rotate 90 degree
  for (int i = 0; i < n; ++i) {
    int xx = m - 1 - y[i], yy = x[i];
    x[i] = xx, y[i] = yy;
  }
  solve();
  for (int i = 0; i < n; ++i) {
    printf("%lld\n", ret[i]);
  }
  return 0;
}

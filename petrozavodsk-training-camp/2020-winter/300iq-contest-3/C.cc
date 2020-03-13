#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>

using int64 = long long;

const int N = 3000 + 10;

bool from[N][N], to[N][N], mark[N][N];
char s[N][N];

int main() {
  int n, m;
  int64 empty = 0;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) scanf("%s", s[i]);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) if (s[i][j] == '.') {
      ++empty;
      if (i == 0 && j == 0) from[i][j] = true;
      if (i && from[i - 1][j]) from[i][j] = true;
      if (j && from[i][j - 1]) from[i][j] = true;
    }
  }
  for (int i = n - 1; i >= 0; --i) {
    for (int j = m - 1; j >= 0; --j) if (s[i][j] == '.') {
      if (i == n - 1 && j == m - 1) to[i][j] = true;
      if (i + 1 < n && to[i + 1][j]) to[i][j] = true;
      if (j + 1 < m && to[i][j + 1]) to[i][j] = true;
    }
  }
  if (!to[0][0]) {
    printf("%lld\n", empty * (empty - 1) / 2);
    return 0;
  }
  mark[n - 1][m - 1] = 1;
  for (int x = 0, y = 0; x != n - 1 || y != m - 1; ) {
    mark[x][y] = 1;
    if (y != m - 1 && to[x][y + 1]) ++y;
    else ++x;
  }
  std::vector<std::pair<int, int>> path;
  for (int x = 0, y = 0; x != n - 1 || y != m - 1; ) {
    path.emplace_back(x, y);
    if (x != n - 1 && to[x + 1][y]) ++x;
    else ++y;
  }
  path.emplace_back(n - 1, m - 1);
  int64 ret = 0, dup = 0;
  for (auto &e: path) {
    if (mark[e.first][e.second]) ++dup;
    else {
      int sx = -1, sy = -1;
      for (int i = 1; i <= e.first; ++i) {
        if (e.second + i >= m) break;
        if (to[e.first - i][e.second + i] && from[e.first - i][e.second + i]) {
          sx = e.first - i, sy = e.second +i;
          break;
        }
      }
      assert(sx != -1 && sy != -1);
      int cnt = mark[0][0] + mark[n - 1][m - 1];
      for (int x = sx, y = sy; x != 0 || y != 0; ) {
        cnt += mark[x][y];
        if (y && from[x][y - 1]) --y;
        else --x;
      }
      for (int x = sx, y = sy; x != n - 1 || y != m - 1; ) {
        cnt += mark[x][y];
        if (x + 1 < n && to[x + 1][y]) ++x;
        else ++y;
      }
      cnt -= mark[sx][sy];
      ret += cnt;
    }
  }
  ret += dup * (empty - 1);
  ret -= dup * (path.size() - dup);
  ret -= dup * (dup - 1) / 2;
  printf("%lld\n", ret);
  return 0;
}

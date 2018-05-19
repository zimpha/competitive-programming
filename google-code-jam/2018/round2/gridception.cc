#include <cstdio>
#include <queue>
#include <cstring>
#include <algorithm>

const int N = 100;

bool mark[N][N];
char a[N][N];
int id[N][N], col[4];
int n, m;

const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};

int bfs(int x, int y) {
  std::queue<std::pair<int, int>> queue;
  mark[x][y] = 1;
  queue.emplace(x, y);
  int ret = 0;
  while (!queue.empty()) {
    int x = queue.front().first;
    int y = queue.front().second;
    ++ret;
    queue.pop();
    for (int i = 0; i < 4; ++i) {
      int xx = x + dx[i], yy = y + dy[i];
      if (xx < 0 || xx >= n || yy < 0 || yy >= m) continue;
      if (col[id[xx][yy]] != a[xx][yy] || mark[xx][yy]) continue;
      mark[xx][yy] = 1;
      queue.emplace(xx, yy);
    }
  }
  return ret;
}

int gao() {
  memset(mark, 0, sizeof(mark));
  int ret = 0;
  for (int x = 0; x < n; ++x) {
    for (int y = 0; y < m; ++y) {
      if (!mark[x][y] && a[x][y] == col[id[x][y]]) {
        ret = std::max(ret, bfs(x, y));
      }
    }
  }
  return ret;
}

bool valid() {
  int s[2][2];
  s[0][0] = col[3];
  s[0][1] = col[2];
  s[1][0] = col[1];
  s[1][1] = col[0];
  int r = 2, c = 2;
  if (*std::max_element(col, col + 4) == *std::min_element(col, col + 4)) r = c = 1;
  else if (s[0][0] == s[0][1] && s[1][0] == s[1][1]) r = 2, c = 1;
  else if (s[0][0] == s[1][0] && s[0][1] == s[1][1]) r = 1, c = 2;
  for (int i = 0; i + r <= n; ++i) {
    for (int j = 0; j + c <= m; ++j) {
      bool flag = true;
      for (int x = 0; x < r; ++x) for (int y = 0; y < c; ++y) {
        flag &= s[x][y] == a[i + x][j + y];
      }
      if (flag) return true;
    }
  }
  return false;
}

int solve() {
  int ret = 0;
  for (int s = -1; s <= n; ++s) {
    for (int t = -1; t <= m; ++t) {
      for (int i = 0; i < n; ++i) {
        for (int j= 0; j < m; ++j) {
          id[i][j] = (i <= s) << 1 | (j <= t);
        }
      }
      for (int mask = 0; mask < 16; ++mask) {
        for (int i = 0; i < 4; ++i) col[i] = mask >> i & 1;
        if (!valid()) continue;
        //for (int i = 0; i < 4; ++i) putchar(col[i] + '0');
        //printf(" %d %d %d\n", s, t, gao());
        ret = std::max(ret, gao());
      }
    }
  }
  return ret;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) {
      scanf("%s", a[i]);
      for(int j = 0; j < m; ++j) {
        a[i][j] = (a[i][j] == 'B');
      }
    }
    int ret = solve();
    printf("Case #%d: %d\n", cas, ret);
  }
  return 0;
}

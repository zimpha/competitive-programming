#include <cstdio>
#include <vector>
#include <numeric>
#include <algorithm>

const int R = 110, N = 1e4 + 10;

char s[R][R], ret[R][R];
int mark[R][R], idx[R][R];
int an, bn, r, c;

const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, 1, -1};

void bfs(int x, int y, char col, int _idx) {
  std::vector<std::pair<int, int>> queue = {{x, y}};
  for (size_t i = 0; i < queue.size(); ++i) {
    int x = queue[i].first, y = queue[i].second;
    idx[x][y] = _idx;
    for (int k = 0; k < 4; ++k) {
      int xx = x + dx[k], yy = y + dy[k];
      if (xx < 0 || xx >= r || yy < 0 || yy >= c) continue;
      if (mark[xx][yy] || s[xx][yy] != col) continue;
      queue.emplace_back(xx, yy);
      mark[xx][yy] = 1;
    }
  }
}

int pa[N], pb[N];

int get(int *dsu, int x) {
  if (x != dsu[x]) dsu[x] = get(dsu, dsu[x]);
  return dsu[x];
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    scanf("%d%d", &r, &c);
    for (int i = 0; i < r; ++i) scanf("%s", s[i]);
    for (int i = 0; i < r; ++i) {
      for (int j = 0; j < c; ++j) {
        idx[i][j] = -1;
        mark[i][j] = 0;
      }
    }
    an = bn = 0;
    for (int i = 0; i < r; ++i) {
      for (int j = 0; j < c; ++j) {
        if (mark[i][j]) continue;
        if (s[i][j] == 'A') bfs(i, j, 'A', an++);
        else bfs(i, j, 'B', bn++);
      }
    }
    for (int i = 0; i < an; ++i) pa[i] = i;
    for (int i = 0; i < bn; ++i) pb[i] = i;
    for (int i = 0; i < r - 1; ++i) {
      ret[i][c - 1] = 0;
      for (int j = 0; j < c - 1; ++j) {
        ret[i][j] = '.';
        if (s[i][j] == s[i + 1][j + 1] && idx[i][j] != idx[i + 1][j + 1]) {
          if (s[i][j] == 'A') {
            int u = get(pa, idx[i][j]), v = get(pa, idx[i + 1][j + 1]);
            if (u != v) pa[u] = v, ret[i][j] = '\\', --an;
          } else {
            int u = get(pb, idx[i][j]), v = get(pb, idx[i + 1][j + 1]);
            if (u != v) pb[u] = v, ret[i][j] = '\\', --bn;
          }
          if (ret[i][j] != '.') continue;
        }
        if (s[i + 1][j] == s[i][j + 1] && idx[i + 1][j] != idx[i][j + 1]) {
          if (s[i + 1][j] == 'A') {
            int u = get(pa, idx[i + 1][j]), v = get(pa, idx[i][j + 1]);
            if (u != v) pa[u] = v, ret[i][j] = '/', --an;
          } else {
            int u = get(pb, idx[i + 1][j]), v = get(pb, idx[i][j + 1]);
            if (u != v) pb[u] = v, ret[i][j] = '/', --bn;
          }
        }
      }
    }
    if (an != 1 || bn != 1) printf("Case #%d: IMPOSSIBLE\n", cas);
    else {
      printf("Case #%d: POSSIBLE\n", cas);
      for (int i = 0; i < r - 1; ++i) puts(ret[i]);
    }
  }
  return 0;
}

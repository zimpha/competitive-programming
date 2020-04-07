#include <cstdio>
#include <cassert>
#include <algorithm>

using int64 = long long;

const int N = 5e5 + 10, inf = 1e9;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

bool mark_s[N], mark_t[N];
int go_s[N][4], go_t[N][4];
int dp_l[N][4], dp_r[N][4];
int down[N];
char s[N];
int n, m;

int id(int x, int y) { return x * m + y; }

void dfs_s(int x, int y) {
  int u = id(x, y);
  if (mark_s[u]) return;
  mark_s[u] = true;
  for (int i = 0; i < 4; ++i) {
    if (go_s[u][i]) dfs_s(x + dx[i], y + dy[i]);
  }
}

void dfs_t(int x, int y) {
  int u = id(x, y);
  if (mark_t[u]) return;
  mark_t[u] = true;
  for (int i = 0; i < 4; ++i) {
    if (go_t[u][i]) dfs_t(x + dx[i], y + dy[i]);
  }
}

int solve_l(int x, int y, int k) {
  int u = id(x, y);
  if (dp_l[u][k] != -inf) return dp_l[u][k];
  int &ret = dp_l[u][k]; ret = 0;
  if (x == n - 1 && y == m - 1 && (k == 1 || k == 2)) return ret;
  if (go_s[u][k]) return ret = solve_l(x + dx[k], y + dy[k], (k + 3) % 4);
  if (k == 0) ret += down[u];
  if (k == 2) ret -= x == n - 1 ? 0 : down[u + m];
  return ret += solve_l(x, y, (k + 1) % 4);
}

int solve_r(int x, int y, int k) {
  int u = id(x, y);
  if (dp_r[u][k] != -inf) return dp_r[u][k];
  int &ret = dp_r[u][k]; ret = 0;
  if (x == n - 1 && y == m - 1 && (k == 1 || k == 2)) return ret;
  if (go_s[u][k]) return ret = solve_r(x + dx[k], y + dy[k], (k + 1) % 4);
  if (k == 0) ret += down[u];
  if (k == 2) ret -= x == n - 1 ? 0 : down[u + m];
  return ret += solve_r(x, y, (k + 3) % 4);
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n * 2 - 1; ++i) {
    if (i & 1) {
      scanf("%s", s);
      for (int j = 0; j < m; ++j) {
        if (s[j] == '^') go_s[id(i / 2 + 1, j)][0] = go_t[id(i / 2, j)][2] = 1;
        if (s[j] == 'v') go_s[id(i / 2, j)][2] = go_t[id(i / 2 + 1, j)][0] = 1;
      }
    } else {
      if (m > 1) scanf("%s", s);
      for (int j = 0; j < m - 1; ++j) {
        if (s[j] == '>') go_s[id(i / 2, j)][1] = go_t[id(i / 2, j + 1)][3] = 1;
        if (s[j] == '<') go_s[id(i / 2, j + 1)][3] = go_t[id(i / 2, j)][1] = 1;
      }
    }
  }
  dfs_s(0, 0);
  dfs_t(n - 1, m - 1);
  for (int i = n - 1; i >= 0; --i) {
    for (int j = 0; j < m; ++j) {
      int u = id(i, j);
      if (i == n - 1) down[u] = 0;
      else down[u] = down[u + m];
      down[u] += mark_s[u] && mark_t[u];
      if (!mark_s[u] || !mark_t[u]) {
        for (int k = 0; k < 4; ++k) go_s[u][k] = 0;
      } else {
        for (int k = 0; k < 4; ++k) {
          int v = id(i + dx[k], j + dy[k]);
          if (go_s[u][k] && (!mark_s[v] || !mark_t[v])) go_s[u][k] = 0;
        }
      }
    }
  }
  for (int i = 0; i < n * m; ++i) {
    for (int j = 0; j < 4; ++j) {
      dp_l[i][j] = -inf;
      dp_r[i][j] = -inf;
    }
  }
  int64 ret = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (!mark_s[id(i, j)] || !mark_t[id(i, j)]) continue;
      ret += std::max(solve_l(i, j, 0) + solve_r(i, j, 3), solve_l(i, j, 2) + solve_r(i, j, 1));
    }
  }
  printf("%lld\n", ret);
  return 0;
}

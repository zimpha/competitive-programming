#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <set>

const int N = 300;

std::vector<int> G[N * N];
int size[N * N], mark[N * N];
int a[N][N], deg[N][N], iv[N * N];
int n, m;

bool check() {
  for (int i = 0; i < n * n; ++i) iv[i] = -1;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (iv[a[i][j]] != -1) return false;
      iv[a[i][j]] = i * n + j;
    }
  }
  for (int i = 0; i < n * n; ++i) {
    for (auto &&j: G[i]) {
      int x1 = iv[i] / n, y1 = iv[i] % n;
      int x2 = iv[j] / n, y2 = iv[j] % n;
      if (abs(x1 - x2) + abs(y1 - y2) > 2) return false;
    }
  }
  return true;
}

void output(bool ret) {
  if (!ret || !check()) puts("-1");
  else {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (j) putchar(' ');
        printf("%d", a[i][j] + 1);
      }
      puts("");
    }
  }
}

int prev[N * N];
void dfs(int u, int p = -1) {
  printf("%d: ", u);
  if (mark[u] == 4) return;
  int mn = 1e9;
  for (auto &&v: G[u]) {
    if (mark[v] == 1 || v == p) continue;
    size[v]--;
    mn = std::min(mn, size[v]);
  }
  std::vector<int> cc;
  for (auto &&v: G[u]) {
    if (mark[v] == 1 || v == p) continue;
    if (size[v] == mn) cc.push_back(v);
  }
  for (auto &&v: cc) {
    prev[v] = u;
    dfs(v, u);
  }
}

void solve1() {
  int p[100];
  for (int i = 0; i < n * n; ++i) p[i] = i;
  do {
    for (int i = 0; i < n * n; ++i) {
      a[i / n][i % n] = p[i];
    }
    if (check()) {
      output(1);
      return;
    }
  } while (std::next_permutation(p, p + n * n));
  output(0);
}

void solve4() {
}

bool solve2() {
  for (int i = 0; i < n * n; ++i) mark[i] = 0;
  int sx = 0, sy = 0;
  for (int nn = n; nn >= 5; --nn) {
    std::vector<int> pc;
    for (int i = 0; i < n * n; ++i) {
      if (!mark[i] && size[i] == 5) pc.push_back(i);
    }
    if (pc.size() != 4) return false;
    for (auto &&x: pc) mark[x] = 4;
    if (sx == 0) a[nn - 1][nn - 1] = pc[0];
    mark[a[nn - 1][nn - 1]] = 1;
    for (int i = 0; i < n * n; ++i) prev[i] = -1;
    dfs(a[nn - 1][nn - 1]);
    std::vector<int> cc;
    if (sx == 0) {
      for (auto &&x: pc) {
        if (prev[x] != -1) cc.push_back(x);
      }
      if (cc.size() != 2) return false;
      a[nn - 1][0] = cc[0];
      a[0][nn - 1] = cc[1];
      printf("%d %d\n", cc[0], cc[1]);
    } else {
      cc = {a[nn - 1][0], a[0][nn - 1]};
    }
    std::vector<int> path;
    for (int u = cc[0]; u != pc[0]; u = prev[u]) {
      path.push_back(u);
      printf("%d ", u);
      mark[u] = 1;
    }
    puts("");
    if (path.size() != nn - 1) return false;
    for (int i = 0; i < nn - 1; ++i) a[nn - 1][i] = path[i];
    path.clear();
    for (int u = cc[1]; u != pc[0]; u = prev[u]) {
      path.push_back(u);
      printf("%d ", u);
      mark[u] = 1;
    }
    puts("");
    if (path.size() != nn - 1) return false;
    for (int i = 0; i < nn - 1; ++i) a[i][nn - 1] = path[i];
    cc.push_back(a[nn - 1][nn - 1]);
    for (auto &&x: G[cc[2]]) {
      if (!mark[x]) a[nn - 2][nn - 2] = x;
    }
    for (auto &&x: G[cc[0]]) {
      if (size[x] == 5) a[nn - 2][0] = x;
    }
    for (auto &&x: G[cc[2]]) {
      if (size[x] == 5) a[0][nn - 2] = x;
    }
  }
  return true;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n * n; ++i) G[i].clear();
    for (int i = 0; i < m; ++i) {
      int u, v;
      scanf("%d%d", &u, &v);
      --u, --v;
      G[u].push_back(v);
      G[v].push_back(u);
      size[u]++;
      size[v]++;
    }
    int tot = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        for (int dx = -2; dx <= 2; ++dx) {
          for (int dy = -2; dy <= 2; ++dy) {
            if (i + dx >= 0 && i + dx < n && j + dy >= 0 && j + dy < n) {
              if (abs(dx) + abs(dy) <= 2 && abs(dx) + abs(dy) >= 1) deg[i][j]++;
            }
          }
        }
        tot += deg[i][j];
      }
    }
    printf("%d %d\n", tot, m * 2);
    if (tot != m * 2) {
      puts("-1");
      return 0;
    }
    if (n <= 3) solve1();
    else output(solve2());
  }
  return 0;
}

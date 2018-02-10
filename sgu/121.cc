#include <cstdio>
#include <vector>

const int N = 200;

std::vector<int> edges[N];
int color[N][N];

void dfs(int u, int c) {
  for (auto &&v: edges[u]) {
    if (color[u][v]) continue;
    color[u][v] = color[v][u] = c;
    dfs(v, c = 3 - c);
  }
}

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    for (int x; scanf("%d", &x) && x; ) {
      edges[i].emplace_back(x - 1);
    }
  }
  for (int i = 0; i < n; ++i) if (edges[i].size() != 2) {
    dfs(i, 1);
  }
  for (int i = 0; i < n; ++i) {
    dfs(i, 1);
  }
  bool valid = true;
  for (int i = 0; i < n; ++i) {
    if (edges[i].size() < 2) continue;
    int state = 0;
    for (auto &&v: edges[i]) state |= color[i][v];
    if (state != 3) valid = false;
  }
  if (!valid) puts("No solution");
  else {
    for (int i = 0; i < n; ++i) {
      for (auto &&u: edges[i]) printf("%d ", color[i][u]);
      puts("0");
    }
  }
  return 0;
}

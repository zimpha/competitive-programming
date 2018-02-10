#include <cstdio>
#include <vector>
#include <algorithm>

const int N = 16000 + 10;

std::vector<int> edges[N];
std::vector<int> roots;
int mins, n, size[N];

void dfs(int u, int p = -1) {
  int mx = 0;
  size[u] = 1;
  for (auto &&v: edges[u]) if (v != p) {
    dfs(v, u);
    size[u] += size[v];
    mx = std::max(mx, size[v]);
  }
  mx = std::max(mx, n - size[u]);
  if (mx < mins) {
    mins = mx;
    roots.clear();
  }
  if (mx == mins) {
    roots.emplace_back(u + 1);
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i < n; ++i) {
    int x, y;
    scanf("%d%d", &x, &y);
    edges[x - 1].emplace_back(y - 1);
    edges[y - 1].emplace_back(x - 1);
  }
  mins = n * 2;
  dfs(0);
  printf("%d %d\n", mins, (int)roots.size());
  std::sort(roots.begin(), roots.end());
  for (auto &&u: roots) printf("%d ", u);
  puts("");
  return 0;
}

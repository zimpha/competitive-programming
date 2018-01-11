#include <cstdio>
#include <vector>

const int N = 1e5 + 10;

std::vector<int> edges[N];
int best[N], down[N];

void dfs(int u, int p = -1) {
  best[u] = down[u] = 0;
  for (auto &&v: edges[u]) if (v != p) {
    dfs(v, u);
    best[u] = std::max(best[u], best[v]);
    best[u] = std::max(best[u], down[u] + down[v] + 1);
    down[u] = std::max(down[u], down[v] + 1);
  }
}

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i < n; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    edges[u].push_back(v);
    edges[v].push_back(u);
  }
  int root;
  scanf("%d", &root);
  dfs(root);
  int q;
  scanf("%d", &q);
  for (int i = 0; i < q; ++i) {
    int s;
    scanf("%d", &s);
    printf("%d\n", best[s]);
  }
  return 0;
}

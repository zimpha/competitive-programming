#include <cstdio>
#include <vector>

const int N = 5000 + 10;

std::vector<int> edges[N];
std::vector<int> ret;

void dfs(int u, int c = 0, int p = -1) {
  if (!c) ret.push_back(u);
  for (auto &&v: edges[u]) if (v != p) {
    dfs(v, c ^ 1, u);
  }
  if (c) ret.push_back(u);
}

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i < n; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    --u, --v;
    edges[u].push_back(v);
    edges[v].push_back(u);
  }
  dfs(0);
  for (int i = 0; i < n; ++i) {
    printf("%d\n", ret[i] + 1);
  }
  return 0;
}

#include <cstdio>
#include <vector>

const int N = 200;

std::vector<int> edges[N];
int col[N];

bool dfs(int u, int c) {
  if (col[u] != -1) return col[u] == c;
  col[u] = c;
  for (auto &&v: edges[u]) {
    if (!dfs(v, c ^ 1)) return false;
  }
  return true;
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    edges[u - 1].push_back(v - 1);
    edges[v - 1].push_back(u - 1);
  }
  for (int i = 0; i < n; ++i) col[i] = -1;
  for (int i = 0; i < n; ++i) {
    if (col[i] == -1) {
      if (!dfs(i, 0)) {
        puts("no");
        return 0;
      }
    }
  }
  puts("yes");
  std::vector<int> choose;
  for (int i = 0; i < n; ++i) {
    if (col[i] == 0) choose.push_back(i + 1);
  }
  printf("%d\n", (int)choose.size());
  for (auto &&x: choose) printf("%d ", x);
  puts("");
  return 0;
}

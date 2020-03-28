#include <cstdio>
#include <vector>

const int N = 1e6 + 10;

std::vector<int> edges[N];

int dfs(int u) {
  int ret = 1;
  for (auto &v: edges[u]) ret += dfs(v);
  return ret;
}

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    int j = i;
    for (int m = i; m; m /= 10) j += m % 10;
    if (j <= n) edges[j].push_back(i);
  }
  printf("%d\n", dfs(n));
  return 0;
}

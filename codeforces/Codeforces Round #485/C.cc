#include <cstdio>
#include <vector>
#include <algorithm>

const int N = 1 << 22;

bool mark[N], input[N];
int n, m;

void dfs(int u) {
  if (mark[u]) return;
  mark[u] = 1;
  if (input[u]) dfs(u ^ ((1 << n) - 1));
  for (int i = 0; i < n; ++i) {
    if (u >> i & 1) dfs(u ^ (1 << i));
  }
}

int main() {
  scanf("%d%d", &n, &m);
  int ret = 0;
  for (int i = 0; i < m; ++i) {
    int x;
    scanf("%d", &x);
    input[x] = 1;
  }
  for (int i = 0; i < (1 << n); ++i) if (input[i]) {
    if (!mark[i]) dfs(i ^ ((1 << n) - 1)), ++ret;
  }
  printf("%d\n", ret);
  return 0;
}

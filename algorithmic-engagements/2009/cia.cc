#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>

using int64 = long long;

const int N = 1e5 + 10;
const int M = 2.5e5 + 10;

std::vector<int> go[N];
int deg[N], weight[N], idx[N];
int a[M], b[M], mark[N];

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &weight[i]);
    idx[i] = i;
  }
  for (int i = 0; i < m; ++i) {
    scanf("%d%d", &a[i], &b[i]);
    --a[i], --b[i];
    ++deg[a[i]], ++deg[b[i]];
  }

  for (int i = 0; i < m; ++i) {
    if (deg[a[i]] < deg[b[i]]) go[a[i]].push_back(b[i]);
    else go[b[i]].push_back(a[i]);
  }
  int64 ret = 0;
  for (int x = 0; x < n; ++x) {
    for (auto &y: go[x]) mark[y] = 1;
    for (auto &y: go[x]) {
      int w = std::max(weight[x], weight[y]);
      for (auto &z: go[y]) if (mark[z]) {
        ret += std::max(weight[z], w);
      }
    }
    for (auto &y: go[x]) mark[y] = 0;
  }
  printf("%lld\n", ret);
  return 0;
}

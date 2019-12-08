#include <cstdio>
#include <vector>
#include <functional>
#include <algorithm>

const int N = 1e5 + 10;
const int inf = 1e9 + 10;

int dsu[N], weight[N], cnt[N];

int root(int x) {
  if (x != dsu[x]) dsu[x] = root(dsu[x]);
  return dsu[x];
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &weight[i]);
  }

  std::vector<std::tuple<int, int, int>> edges;
  for (int i = 0; i < m; ++i) {
    int x, y, z;
    scanf("%d%d%d", &x, &y, &z);
    edges.emplace_back(z, x - 1, y - 1);
  }

  std::sort(edges.begin(), edges.end());

  for (int i = 0; i < n; ++i) dsu[i] = i;
  int ret = 0;
  for (auto &e: edges) {
    int w = std::get<0>(e);
    int a = root(std::get<1>(e));
    int b = root(std::get<2>(e));
    if (a != b) {
      dsu[a] = b;
      weight[b] = std::min(weight[b] + weight[a], inf);
      cnt[b] += cnt[a];
    }
    cnt[b]++;
    if (weight[b] >= w) {
      ret += cnt[b];
      cnt[b] = 0;
    }
  }
  printf("%d\n", m - ret);
  return 0;
}

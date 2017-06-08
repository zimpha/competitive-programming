#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <random>

const int N = 200000 + 10;
using ld = long double;
using ll = long long;

std::pair<ld, int> hash[N];
std::vector<int> edges[N];
bool mark[N];
ld sum[N];

void dfs(int u, ld val) {
  if (mark[u]) return;
  mark[u] = true;
  sum[u] += val;
  for (auto &&v: edges[u]) {
    dfs(v, val);
  }
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) {
    sum[i] = 0;
  }
  for (int i = 0; i < m; ++i) {
    int a, b;
    scanf("%d%d", &a, &b);
    edges[b - 1].push_back(a - 1);
  }
  std::default_random_engine generator;
  std::uniform_real_distribution<double> distribution(0.0,1.0);
  for (int it = 0; it < 100; ++it) {
    for (int i = 0; i < n; ++i) {
      hash[i] = {ld(distribution(generator)), i};
      mark[i] = false;
    }
    std::sort(hash, hash + n);
    for (int i = 0; i < n; ++i) {
      if (!mark[hash[i].second]) {
        dfs(hash[i].second, hash[i].first);
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    ld est = 100 / sum[i] - 1;
    if (est < 1) est = 1;
    if (est > n) est = n;
    printf("%d\n", (int)est);
  }
  return 0;
}

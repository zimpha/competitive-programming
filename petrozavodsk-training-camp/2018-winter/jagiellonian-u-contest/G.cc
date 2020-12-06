#include <cstdio>
#include <vector>
#include <algorithm>

const int N = 20, M = 1 << N;

std::vector<int> vs[M];
std::vector<std::pair<int, int>> edges[N + 1];
int dsu[M];

int get(int x) {
  if (dsu[x] != x) dsu[x] = get(dsu[x]);
  return dsu[x];
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i <= n; ++i) edges[i].clear();
    std::vector<int> a(m), dist(1 << n, -1), belong(1 << n, -1);
    std::vector<int> queue;
    for (int i = 0; i < m; ++i) {
      static char s[30];
      scanf("%s", s);
      for (int j = 0; j < n; ++j) {
        a[i] |= (s[j] == 'L') << j;
      }
      queue.push_back(a[i]);
      dist[a[i]] = 0;
      vs[i] = {a[i]};
      belong[a[i]] = i;
      dsu[i] = i;
    }
    for (size_t i = 0; i < queue.size(); ++i) {
      int u = queue[i];
      for (int j = 0; j < n; ++j) {
        int v = u ^ (1 << j);
        if (dist[v] == -1) {
          vs[belong[u]].push_back(v);
          dist[v] = dist[u] + 1;
          belong[v] = belong[u];
          queue.push_back(v);
        }
      }
    }
    std::vector<bool> mark(m);
    for (int i = 0; i < m; ++i) {
      for (auto &u: vs[i]) {
        for (int b = 0; b < n; ++b) {
          int j = belong[u ^ (1 << b)];
          if (i == j) continue;
          if (!mark[j]) edges[__builtin_popcount(a[i] ^ a[j])].emplace_back(i, j);
          mark[j] = 1;
        }
      }
      for (auto &u: vs[i]) {
        for (int b = 0; b < n; ++b) {
          mark[belong[u ^ (1 << b)]] = 0;
        }
      }
    }
    int ret = 0;
    for (int i = 0; i <= n; ++i) {
      for (auto &e: edges[i]) {
        int x = get(e.first);
        int y = get(e.second);
        if (x != y) {
          ret += i;
          dsu[x] = y;
        }
      }
    }
    printf("%d\n", ret);
  }
  return 0;
}

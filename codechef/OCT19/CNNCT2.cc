#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <queue>

const int N = 300, M = 300;

namespace dsu {
int parent[N];
void init(int n) {
  for (int i = 0; i < n; ++i) parent[i] = i;
}
int root(int x) {
  if (x != parent[x]) parent[x] = root(parent[x]);
  return parent[x];
}
void merge(int a, int b) {
  a = root(a), b = root(b);
  parent[a] = b;
}
}

namespace matroid {
int a[2][M], b[2][M], m;
int choose[M];
int ok[2][M], dist[M], parent[M];
int queue[M];
std::vector<int> edges[M];
void init(int _m) {
  m = _m;
  for (int i = 0; i < m; ++i) choose[i] = 0;
}
void add_edge(int e, int i, int _a, int _b) {
  a[e][i] = _a, b[e][i] = _b;
}
bool aug(int n) {
  for (int i = 0; i < m; ++i) {
    edges[i].clear();
    ok[0][i] = ok[1][i] = 0;
  }
  for (int e = 0; e < 2; ++e) {
    dsu::init(n);
    for (int i = 0; i < m; ++i) if (choose[i]) {
      dsu::merge(a[e][i], b[e][i]);
    }
    for (int i = 0; i < m; ++i) if (!choose[i]) {
      ok[e][i] = dsu::root(a[e][i]) != dsu::root(b[e][i]);
    }
  }
  for (int i = 0; i < m; ++i) if (!choose[i]) {
    if (ok[0][i] && ok[1][i]) {
      choose[i] = 1;
      return true;
    }
  }
  for (int e = 0; e < 2; ++e) {
    for (int x = 0; x < m; ++x) if (choose[x]) {
      dsu::init(n);
      for (int i = 0; i < m; ++i) if (choose[i] && i != x) {
        dsu::merge(a[e][i], b[e][i]);
      }
      for (int y = 0; y < m; ++y) if (!choose[y]) {
        if (dsu::root(a[e][y]) != dsu::root(b[e][y])) {
          if (e == 0) edges[x].push_back(y);
          else edges[y].push_back(x);
        }
      }
    }
  }
  for (int i = 0; i < m; ++i) dist[i] = parent[i] = -1;
  int h = 0, t = 0;
  for (int i = 0; i < m; ++i) {
    if (ok[0][i]) dist[i] = 0, queue[t++] = i;
  }
  int best = -1;
  for (; h < t; ++h) {
    int u = queue[h];
    if (ok[1][u]) { best = u; break; }
    for (auto &v: edges[u]) if (dist[v] == -1) {
      dist[v] = dist[u] + 1;
      queue[t++] = v;
      parent[v] = u;
    }
  }
  for (int x = best; x != -1; x = parent[x]) {
    choose[x] ^= 1;
  }
  return best != -1;
}
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, m;
    scanf("%d%d", &n, &m);
    matroid::init(m);
    for (int e = 0; e < 2; ++e) {
      for (int i = 0; i < m; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        matroid::add_edge(e, i, a - 1, b - 1);
      }
    }
    int ret = n * 2 - 2;
    while (matroid::aug(n)) --ret;
    printf("%d\n", ret);
  }
  return 0;
}

#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

const int N = 110, M = 100, inf = 1e9;

using pii = std::pair<int, int>;

namespace dsu {
int parent[N], cnt;
void init(int n) {
  cnt = n;
  for (int i = 0; i < n; ++i) parent[i] = i;
}
int root(int x) {
  if (x != parent[x]) parent[x] = root(parent[x]);
  return parent[x];
}
void merge(int a, int b) {
  a = root(a), b = root(b);
  if (a != b) parent[a] = b, --cnt;
}
}

pii operator + (const pii &a, const pii &b) {
  return {a.first + b.first, a.second + b.second};
}

namespace matroid {
int a[M], b[M], w[M], c[M], m;
int choose[M], graph[M][M];
void add_edge(int _a, int _b, int _w, char _c) {
  a[m] = _a, b[m] = _b, w[m] = _w, c[m] = _c;
  choose[m++] = 0;
}
bool aug(int n) {
  for (int i = 0; i < m; ++i) {
    memset(graph[i], 0, sizeof(*graph[i]) * m);
  }
  std::vector<int> st, ed;
  // S - I - y + x \in I1 or I2
  // S - I - y \in I1 or I2
  for (char src: std::vector<char>{'R', 'B'}) {
    for (int y = 0; y < m; ++y) if (!choose[y]) {
      dsu::init(n);
      for (int i = 0; i < m; ++i) if (!choose[i] && i != y && c[i] != src) {
        dsu::merge(a[i], b[i]);
      }
      if (dsu::cnt == 1) {
        if (src == 'R') st.push_back(y);
        else ed.push_back(y);
      }
      for (int x = 0; x < m; ++x) if (choose[x]) {
        if (dsu::cnt == 1 || (c[x] != src && dsu::cnt == 2 && dsu::root(a[x]) != dsu::root(b[x]))) {
          if (src == 'R') graph[x][y] = true;
          else graph[y][x] = true;
        }
      }
    }
  }
  if (st.empty() || ed.empty()) return false;
  std::vector<pii> dist(m, {inf, inf});
  std::vector<int> mark(m,  0), parent(m, -1);
  std::queue<int> queue;
  for (auto &x: st) {
    dist[x] = {-w[x], 0};
    queue.push(x);
    mark[x] = true;
  }
  while (!queue.empty()) {
    int u = queue.front(); queue.pop();
    mark[u] = false;
    for (int v = 0; v < m; ++v) if (graph[u][v]) {
      pii cost = dist[u] + pii(choose[v] ? w[v] : -w[v], 1);
      if (dist[v] > cost) {
        dist[v] = cost;
        parent[v] = u;
        if (!mark[v]) queue.push(v);
        mark[v] = true;
      }
    }
  }
  int best = -1;
  for (auto &x: ed) if (dist[x].first != inf) {
    if (best == -1 || dist[x] < dist[best]) best = x;
  }
  for (int x = best; x != -1; x = parent[x]) {
    choose[x] ^= 1;
  }
  return best != -1;
}
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; ++i) {
    int a, b, w;
    char c;
    scanf("%d%d%d %c", &a, &b, &w, &c);
    matroid::add_edge(a - 1, b - 1, w, c);
  }
  std::vector<int> ret(m + 1, -1);
  for (int i = m; i >= 1; --i) {
    ret[i] = 0;
    for (int j = 0; j < m; ++j) {
      if (!matroid::choose[j]) ret[i] += matroid::w[j];
    }
    if (!matroid::aug(n)) break;
  }
  for (int i = 1; i <= m; ++i) {
    printf("%d\n", ret[i]);
  }
  return 0;
}

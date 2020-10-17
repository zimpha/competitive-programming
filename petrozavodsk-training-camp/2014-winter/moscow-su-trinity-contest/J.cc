#include <cstdio>
#include <vector>

using int64 = long long;

struct point {
  int64 x, y;
  point(int64 x = 0, int64 y = 0): x(x), y(y) {}
  point operator + (const point &rhs) const {
    return {x + rhs.x, y + rhs.y};
  }
  point operator - (const point &rhs) const {
    return {x + rhs.x, y + rhs.y};
  }
  int64 det(const point &rhs) const {
    return x * rhs.y - y * rhs.x;
  }
};

// Given the (a[i], b[i]) of a graph with n vertices, find all triangles in the graph.
// Time Complexity: O(m sqrt m)
std::vector<std::tuple<int, int, int>> triangle(int n, int m, const std::vector<int> &a, const std::vector<int> &b) {
  std::vector<int> deg(n);
  for (int i = 0; i < m; ++i) {
    deg[a[i]]++; deg[b[i]]++;
  }
  std::vector<std::vector<int>> edges(n);
  for (int i = 0; i < m; ++i) {
    if (deg[a[i]] < deg[b[i]] || (deg[a[i]] == deg[b[i]] && a[i] < b[i])) edges[a[i]].push_back(b[i]);
    else edges[b[i]].push_back(a[i]);
  }
  std::vector<bool> mark(n);
  std::vector<std::tuple<int, int, int>> ret;
  for (int u = 0; u < n; ++u) {
    for (auto &v: edges[u]) mark[v] = 1;
    for (auto &v: edges[u]) {
      for (auto &w: edges[v]) if (mark[w]) {
        ret.emplace_back(u, v, w);
      }
    }
    for (auto &v: edges[u]) mark[v] = 0;
  }
  return ret;
}

int main() {
  int n, m;
  scanf("%d", &n);
  std::vector<point> p(n);
  for (int i = 0; i < n; ++i) scanf("%lld%lld", &p[i].x, &p[i].y);
  scanf("%d", &m);
  std::vector<int> t(m), a(m), b(m);
  std::vector<int> u, v;
  for (int i = 0; i < m; ++i) {
    scanf("%d%d%d", &t[i], &a[i], &b[i]);
    if (t[i] == 1) u.push_back(a[i]), v.push_back(b[i]);
  }
  auto tri = triangle(n, u.size(), u, v);
  std::vector<int> dsu(tri.size() + 1);
  return 0;
}

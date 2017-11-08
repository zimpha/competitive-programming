#include <cmath>
#include <cstdio>
#include <vector>
#include <tuple>

const double eps = 1e-8;

struct point {
  double x, y;
  point(double x = 0, double y = 0): x(x), y(y) {}
  point operator + (const point &rhs) const {
    return point(x + rhs.x, y + rhs.y);
  }
  point operator - (const point &rhs) const {
    return point(x - rhs.x, y - rhs.y);
  }
  double det(const point &rhs) const {
    return x * rhs.y - y * rhs.x;
  }
  double dot(const point &rhs) const {
    return x * rhs.x + y * rhs.y;
  }
  double norm2() const {
    return x * x + y * y;
  }
};

int main() {
  int n;
  scanf("%d", &n);
  std::vector<point> p(n + 1);
  std::vector<double> r(n + 1);
  for (int i = 0; i <= n; ++i) {
    scanf("%lf%lf%lf", &p[i].x, &p[i].y, &r[i]);
  }
  for (int i = 0; i < n; ++i) {
    r[i] += r[n];
    p[i] = p[i] - p[n];
  }
  std::vector<std::tuple<int, int, double>> edges;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (i == j) continue;
      if ((r[i] + r[j]) * (r[i] + r[j]) > (p[i] - p[j]).norm2() + eps) {
        edges.emplace_back(i, j, atan2(p[i].det(p[j]), p[i].dot(p[j])));
      }
    }
  }
  std::vector<double> dis(n);
  for (int i = 0; i < n; ++i) {
    for (auto &&e: edges) {
      int u = std::get<0>(e), v = std::get<1>(e);
      double w = std::get<2>(e);
      if (dis[v] > dis[u] + w + eps) {
        dis[v] = dis[u] + w;
      }
    }
  }
  bool update = false;
  for (auto &&e: edges) {
    int u = std::get<0>(e), v = std::get<1>(e);
    double w = std::get<2>(e);
    if (dis[v] > dis[u] + w + eps) {
      update = true;
      break;
    }
  }
  puts(update ? "NO" : "YES");
  return 0;
}

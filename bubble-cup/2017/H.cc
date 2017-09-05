#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>

using int64 = long long;

const int N = 210, M = 60;

struct Point {
  int64 x, y;
  Point() {}
  Point(int64 x, int64 y): x(x), y(y) {}
  bool operator < (const Point &rhs) const {
    return x < rhs.x || (x == rhs.x && y < rhs.y);
  }
  Point operator + (const Point &rhs) const {
    return Point(x + rhs.x, y + rhs.y);
  }
  Point operator - (const Point &rhs) const {
    return Point(x - rhs.x, y - rhs.y);
  }
  int64 dot(const Point &rhs) const {
    return x * rhs.x + y * rhs.y;
  }
  int64 det(const Point &rhs) const {
    return x * rhs.y - y * rhs.x;
  }
} P[N];

int n, m;

inline int sgn(int64 x) {
  return x < 0 ? -1 : (x > 0);
}

inline int sgn(Point a) {
  return a.x > 0 || (a.x == 0 && a.y > 0);
}

bool cmp(const Point &a, const Point &b) {
  int sa = sgn(a), sb = sgn(b);
  if (sa == sb) return a.det(b) > 0;
  else return sa > sb;
}

struct edge_t {
  Point v;
  int a, b;
  edge_t(Point _v, int _a, int _b): v(_v), a(_a), b(_b) {}
  bool operator < (const edge_t &rhs) const {
    return cmp(v, rhs.v);
  }
};

int64 dp[N][N];

double solve(int s) {
  std::vector<Point> pts = {{0, 0}};
  for (int i = 0; i < n; ++i) {
    if (i == s) continue;
    if (P[i].x > P[s].x || (P[i].x == P[s].x && P[i].y > P[s].y)) {
      pts.push_back(P[i] - P[s]);
    }
  }
  std::sort(pts.begin() + 1, pts.end(), cmp);
  std::vector<edge_t> edge;
  int n = pts.size();
  for (int i = 1; i < n; ++i) {
    edge.emplace_back(pts[i] - pts[0], 0, i);
    edge.emplace_back(pts[0] - pts[i], i, 0);
  }
  for (int i = 1; i + 1 < n; ++i) {
    edge.emplace_back(pts[i + 1] - pts[i], i, i + 1);
    edge.emplace_back(pts[i] - pts[i + 1], i + 1, i);
    Point w = pts[i + 1];
    for (int j = i + 2; j < n; ++j) {
      if ((pts[j] - pts[i]).det(w - pts[i]) < 0) {
        w = pts[j];
        edge.emplace_back(pts[j] - pts[i], i, j);
        edge.emplace_back(pts[i] - pts[j], j, i);
      }
    }
  }
  std::sort(edge.begin(), edge.end());
  memset(dp, -1, sizeof(dp));
  dp[0][0] = 0;
  for (auto &&e: edge) {
    int a = e.a, b = e.b;
    for (int i = 0; i < m; ++i) {
      if (dp[a][i] == -1) continue;
      dp[b][i + 1] = std::max(dp[b][i + 1], dp[a][i] + pts[a].det(pts[b]));
    }
  }
  return dp[0][m];
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0, b; i < n; ++ i) {
    scanf("%lld%lld", &P[i].x, &P[i].y);
  }
  double ret = 0;
  for (int i = 0; i < n; ++i) {
    ret = std::max(ret, solve(i));
  }
  printf("%.2f\n", ret * 0.5);
  return 0;
}
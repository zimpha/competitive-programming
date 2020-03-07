#include <cstdio>
#include <cassert>
#include <cmath>
#include <vector>
#include <algorithm>
#include <set>

const double eps = 1e-8;

inline double cmp(double a, double b, double e = eps) {
  return fabs(a - b) >= e + fabs(a) * e ? a - b : 0;
}

struct point {
  double x, y, z;
  bool operator < (const point &rhs) const {
    return cmp(x, rhs.x) < 0 || (cmp(x, rhs.x) == 0 && cmp(y, rhs.y) < 0) || (cmp(x, rhs.x) == 0 && cmp(y, rhs.y) == 0 && cmp(z, rhs.z) < 0);
  }
  bool operator == (const point &rhs) const {
    return cmp(x, rhs.x) == 0 && cmp(y, rhs.y) == 0 && cmp(z, rhs.z) == 0;
  }
  point(double x = 0, double y = 0, double z = 0): x(x), y(y), z(z) {}
  point operator + (const point &rhs) const {
    return point(x + rhs.x, y + rhs.y, z + rhs.z);
  }
  point operator - (const point &rhs) const {
    return point(x - rhs.x, y - rhs.y, z - rhs.z);
  }
  point operator * (const double k) const {
    return point(x * k, y * k, z * k);
  }
  void rot_xy(double px, double py) {
    double cs = py / hypot(px, py);
    double si = px / hypot(px, py);
    double xx = x * cs - y * si;
    double yy = x * si + y * cs;
    x = xx, y = yy;
  }
  void rot_yz(double py, double pz) {
    double cs = pz / hypot(py, pz);
    double si = py / hypot(py, pz);
    double yy = y * cs - z * si;
    double zz = y * si + z * cs;
    y = yy, z = zz;
  }
};

const int N = 200 + 10;

struct Tree {
  std::vector<int> edges[N];
  point pts[N];
  int parent[N], depth[N];
  int n, extra;
  void build() {
    for (int i = 0; i < n; ++i) {
      scanf("%lf%lf%lf", &pts[i].x, &pts[i].y, &pts[i].z);
    }
    for (int i = 1; i < n; ++i) {
      int u, v;
      scanf("%d%d", &u, &v);
      u = (u - 1) % n, v = (v - 1) % n;
      edges[u].push_back(v);
      edges[v].push_back(u);
    }
  }
  void dfs(int u, double scale, point o, int p = -1) {
    parent[u] = p;
    depth[u] = p == -1 ? 0 : depth[p] + 1;
    for (auto &v: edges[u]) if (v != p) {
      auto t = pts[v];
      pts[v] = (t - o) * scale + pts[u];
      dfs(v, scale, t, u);
    }
    if (extra == -1 && p != -1) {
      if (cmp(pts[p].x, 0) == 0 && cmp(pts[p].y, 0) == 0) {
        if (cmp(pts[u].x, 0) != 0 || cmp(pts[u].y, 0) != 0) extra = u;
      }
    }
  }
  void rot_xy(double px, double py) {
    if (cmp(px, 0) == 0 && cmp(py, 0) == 0) return;
    for (int i = 0; i < n; ++i) pts[i].rot_xy(px, py);
  }
  void rot_yz(double py, double pz) {
    if (cmp(pz, 0) == 0 && cmp(py, 0) == 0) return;
    for (int i = 0; i < n; ++i) pts[i].rot_yz(py, pz);
  }
  void norm(int a, int b) {
    point e = pts[a];
    for (int i = 0; i < n; ++i) pts[i] = pts[i] - e;
    rot_xy(pts[b].x, pts[b].y);
    rot_yz(pts[b].y, pts[b].z);
    assert(cmp(pts[b].z, 0) > 0);
    double scale = 1.0 / pts[b].z;
    extra = -1;
    dfs(a, scale, pts[a]);
  }
  void print() {
    for (int i = 0; i < n; ++i) {
      printf("%.10f %.10f %.10f\n", pts[i].x, pts[i].y, pts[i].z);
    }
    for (int i = 0; i < n; ++i) for (auto &j: edges[i]) {
      if (i < j) printf("%d %d\n", i, j);
    }
  }
} t1, t2;

std::vector<int> check(const Tree &t1, const Tree &t2) {
  int n = t1.n;
  std::vector<int> v1(n), v2(n);
  for (int i = 0; i < n; ++i) v1[i] = v2[i] = i;
  std::sort(v1.begin(), v1.end(), [&](int a, int b) {
    return t1.pts[a] < t1.pts[b];
  });
  std::sort(v2.begin(), v2.end(), [&](int a, int b) {
    return t2.pts[a] < t2.pts[b];
  });
  for (int i = 0; i < n; ++i) {
    if (!(t1.pts[v1[i]] == t2.pts[v2[i]])) return {};
  }
  std::vector<int> pos1(n), pos2(n);
  for (int i = 0; i < n; ++i) pos1[v1[i]] = pos2[v2[i]] = i;
  std::vector<std::pair<int, int>> e1, e2;
  for (int i = 0; i < n; ++i) {
    for (auto &j: t1.edges[i]) e1.emplace_back(pos1[i], pos1[j]);
    for (auto &j: t2.edges[i]) e2.emplace_back(pos2[i], pos2[j]);
  }
  std::sort(e1.begin(), e1.end());
  std::sort(e2.begin(), e2.end());
  if (e1 == e2) return pos2;
  else return {};
}

int main() {
  int n;
  scanf("%d", &n);
  t1.n = t2.n = n;
  t1.build();
  t2.build();
  for (int i = 0; i < n; ++i) if (t1.edges[i].size() == 1) {
    int a = i, b = t1.edges[i][0];
    t1.norm(a, b);
    break;
  }
  int depth = -1;
  if (t1.extra != -1) {
    depth = t1.depth[t1.extra];
    t1.rot_xy(t1.pts[t1.extra].x, t1.pts[t1.extra].y);
  }
  std::set<std::vector<int>> mp;
  for (int i = 0; i < n; ++i) if (t2.edges[i].size() == 1) {
    auto t3 = t2;
    int a = i, b = t2.edges[i][0];
    t3.norm(a, b);
    std::vector<int> candidates;
    for (int j = 0; j < n; ++j) if (j != a && j != b) {
      int p = t3.parent[j];
      if (cmp(t3.pts[p].x, 0) != 0 || cmp(t3.pts[p].y, 0) != 0) continue;
      if (cmp(t3.pts[j].x, 0) == 0 && cmp(t3.pts[j].y, 0) == 0) continue;
      if (depth != t3.depth[j]) continue;
      candidates.push_back(j);
    }
    if (candidates.empty()) {
      auto p = check(t1, t3);
      if (!p.empty()) mp.insert(p);
    }
    for (auto &j: candidates) {
      t3.rot_xy(t3.pts[j].x, t3.pts[j].y);
      auto p = check(t1, t3);
      if (!p.empty()) mp.insert(p);
    }
  }
  printf("%d\n", (int)mp.size());
  return 0;
}

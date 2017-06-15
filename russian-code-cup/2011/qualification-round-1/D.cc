// given 2n lines, match them into n pairs, lines in each pair are parallel
// the distance of the lines in each pair is the same and minimum
#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>

const int N = 4000 + 10;

struct point {
  int x, y;
  point(int x = 0, int y = 0): x(x), y(y) {}
  point operator - (const point &r) const {
    return point(x - r.x, y - r.y);
  }
  int det(const point &r) const {
    return x * r.y - y * r.x;
  }
  double norm() const {
    return hypot(x, y);
  }
} P[N], Q[N];

std::vector<std::pair<double, int>> candidate[N];
std::vector<int> edges[N];
int deg[N];

bool parallel(const point &a, const point &b, const point &c, const point &d) {
  return (b - a).det(d - c) == 0;
}

double dis(const point &a, const point &b, const point &c, const point &d) {
  return std::abs((b - a).det(c - a)) / (b - a).norm();
}

int main() {
  int n;
  scanf("%d", &n);
  n *= 2;
  for (int i = 0; i < n; ++i) {
    scanf("%d%d%d%d", &P[i].x, &P[i].y, &Q[i].x, &Q[i].y);
  }
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      if (!parallel(P[i], Q[i], P[j], Q[j])) continue;
      candidate[i].emplace_back(dis(P[i], Q[i], P[j], Q[j]), j);
    }
    std::sort(candidate[i].begin(), candidate[i].end());
  }
  for (auto &&e: candidate[0]) {
    double d = e.first;
    for (int i = 0; i < n; ++i) {
      deg[i] = 0;
      edges[i].clear();
    }
    for (int i = 0; i < n; ++i) {
      auto it = std::lower_bound(candidate[i].begin(), candidate[i].end(), std::make_pair(d, -1));
      while (it < candidate[i].end() && fabs(it->first - d) < 1e-8) {
        edges[i].push_back(it->second);
        edges[it->second].push_back(i);
        deg[i]++;
        deg[it->second]++;
        ++it;
      }
    }
    bool find = true;
    std::vector<bool> mark(n, false);
    for (int i = 0; i < n && find; ++i) {
      if (deg[i] == 0) find = false;
    }
    if (!find) continue;
    for (int i = 0; i < n && find; ++i) {
      if (deg[i] == 1 && !mark[i]) {
        int cnt = 1;
        mark[i] = true;
        for (int u = i; ; cnt += 1) {
          int nx = -1;
          for (auto &&v: edges[u]) if (!mark[v]) {
            nx = v;
          }
          if (nx == -1) break;
          u = nx;
          mark[u] = true;
        }
        if (cnt & 1) find = false;
      }
    }
    if (find) {
      printf("%.20f\n", d);
      return 0;
    }
  }
  puts("-1");
  return 0;
}

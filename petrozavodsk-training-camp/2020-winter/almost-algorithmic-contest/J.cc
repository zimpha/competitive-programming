#include <cmath>
#include <cstdio>
#include <tuple>
#include <vector>
#include <algorithm>

const int N = 300;
const double pi = acos(-1.0);

double fix(double x) {
  while (x < 0) x += pi * 2;
  while (x >= pi * 2) x -= pi * 2;
  return x;
}

double dist[N][N], now[N][N], ang[N][N];
std::pair<double, double> acc[N][N];

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> x(n), y(n);
  std::vector<int> p(n), q(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d%d", &x[i], &y[i]);
    p[i] = i;
    for (int j = 0; j <= i; ++j) {
      dist[i][j] = dist[j][i] = hypot(x[i] - x[j], y[i] - y[j]);
      acc[i][j] = acc[j][i] = {0, -1};
      ang[i][j] = fix(atan2(y[j] - y[i], x[j] - x[i]));
      ang[j][i] = fix(atan2(y[i] - y[j], x[i] - x[j]));
    }
  }
  std::vector<std::tuple<double, int, int>> events;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (i == j) continue;
      events.emplace_back(fix(pi / 2 + ang[i][j]), i, j);
    }
  }
  std::sort(events.begin(), events.end());
  std::sort(p.begin(), p.end(), [&](int a, int b) {
    return x[a] == x[b] ? y[a] > y[b] : x[a] < x[b];
  });
  for (int i = 0; i < n; ++i) q[p[i]] = i;

  double ret = 0;

  auto add = [&](int i, int j, std::pair<double, double> v) {
    if (acc[i][j].second != -1) {
      double al = acc[i][j].first, ar = v.first;
      double st = acos(std::max(-1.0, -acc[i][j].second / dist[i][j]));
      ret += std::max(0., std::min(ang[i][j] - pi / 2, ar) - std::max(ang[i][j] - st, al));
      ret += std::max(0., std::min(ang[i][j] + pi * 2 - pi / 2, ar) - std::max(ang[i][j] + pi * 2 - st, al));

      ret += std::max(0., std::min(ang[i][j] - pi * 2 + st, ar) - std::max(ang[i][j] - pi * 2 + pi / 2, al));
      ret += std::max(0., std::min(ang[i][j] + st, ar) - std::max(ang[i][j] + pi / 2, al));
    }
    acc[i][j] = v;
  };

  double tmp = 1e18;
  for (int i = 0; i < n; ++i) {
    for (int j = i - 1; j >= 0; --j) {
      tmp = std::min(tmp, dist[p[i]][p[j]]);
      now[p[i]][p[j]] = tmp;
      add(p[i], p[j], {0, tmp});
    }
  }
  
  for (auto &e: events) {
    double ang = std::get<0>(e);
    int a = std::get<1>(e);
    int b = std::get<2>(e);
    if (q[a] > q[b]) std::swap(a, b);
    int ai = q[a], bi = q[b];
    std::swap(q[a], q[b]);
    std::swap(p[q[a]], p[q[b]]);
    if (ai + 1 != bi) continue;
    tmp = 1e18;
    if (ai >= 2) tmp = now[p[ai - 1]][p[0]];
    for (int j = ai - 1; j >= 0; --j) {
      tmp = std::min(tmp, dist[p[ai]][p[j]]);
      now[p[ai]][p[j]] = tmp;
      add(p[ai], p[j], {ang, tmp});
    }
    add(b, a, {ang, -1});
    for (int j = bi - 1; j >= 0; --j) {
      tmp = std::min(tmp, dist[p[bi]][p[j]]);
      now[p[bi]][p[j]] = tmp;
      add(p[bi], p[j], {ang, tmp});
    }
    for (int i = bi + 1; i < n; ++i) {
      tmp = now[p[i]][p[bi]];
      for (int j = bi; j >= ai; --j) {
        tmp = std::min(tmp, dist[p[i]][p[j]]);
        now[p[i]][p[j]] = tmp;
        add(p[i], p[j], {ang, tmp});
      }
    }
  }
  tmp = 1e18;
  for (int i = 0; i < n; ++i) {
    for (int j = i - 1; j >= 0; --j) {
      tmp = std::min(tmp, dist[p[i]][p[j]]);
      add(p[i], p[j], {pi * 2, tmp});
    }
  }
  printf("%.10f\n", ret / (pi * 2));
  return 0;
}

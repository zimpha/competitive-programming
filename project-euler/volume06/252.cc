#include <bits/stdc++.h>
using namespace std;
const double eps = 1e-9;
const int MAXN = 1000;

struct Point {
  int x, y;
  Point() {}
  Point(int a, int b): x(a), y(b) {}
  bool operator < (const Point &rhs) const {
    return y < rhs.y || (y == rhs.y && x < rhs.x);
  }
  Point operator + (const Point &rhs) const {
    return Point(x + rhs.x, y + rhs.y);
  }
  Point operator - (const Point &rhs) const {
    return Point(x - rhs.x, y - rhs.y);
  }
  int det(const Point &rhs) const {
    return x * rhs.y - y * rhs.x;
  }
  int dot(const Point &rhs) const {
    return x * rhs.x + y * rhs.y;
  }
  double len() const {
    return hypot(x, y);
  }
} P[MAXN], Q[MAXN];

bool cmp(const Point &a, const Point &b) {
  int tmp = a.det(b);
  if (tmp != 0) return tmp > 0;
  return b.len() > a.len() + eps;
}

int dp[MAXN][MAXN], seq[MAXN];

int solve(int vv, int n) {
  int m = 0;
  for (int i = 0; i < n; ++i) {
    if (P[vv] < P[i]) Q[m++] = P[i] - P[vv];
  }
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < m; ++j) {
      dp[i][j] = 0;
    }
  }
  sort(Q, Q + m, cmp);
  int ret = 0;
  for (int t = 1, i, j; t < m; ++t) {
    int len = 0;
    for (i = t - 1; i >= 0 && Q[t].det(Q[i]) == 0; --i);
    while (i >= 0) {
      int v = Q[i].det(Q[t]);
      seq[len++] = i;
      for (j = i - 1; j >= 0 && (Q[i] - Q[t]).det(Q[j] - Q[t]) > 0; --j);
      if (j >= 0) v += dp[i][j];
      ret = max(ret, v);
      dp[t][i] = v; i = j;
    }
    for (i = len - 2; i >= 0; --i) {
      dp[t][seq[i]] = max(dp[t][seq[i]], dp[t][seq[i + 1]]);
    }
  }
  return ret;
}

int run(int n) {
  int s = 290797;
  for (int i = 0; i < n; ++i) {
    s = 1ll * s * s % 50515093;
    P[i].x = s % 2000 - 1000;
    s = 1ll * s * s % 50515093;
    P[i].y = s % 2000 - 1000;
  }
  int ret = 0;
  for (int i = 0; i < n; ++i) {
    ret = max(ret, solve(i, n));
  }
  return ret;
}

int main() {
  cout << fixed << run(20) / 2.0 << endl;
  cout << fixed << run(500) / 2.0 << endl;
  return 0;
}

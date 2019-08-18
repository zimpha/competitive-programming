#include <cstdio>
#include <vector>
#include <algorithm>

using int64 = long long;
using flt = int64;

struct point {
  flt x, y;
  point(flt x = 0, flt y = 0): x(x), y(y) {}
  point operator + (const point &rhs) const {
    return point(x + rhs.x, y + rhs.y);
  }
  point operator - (const point &rhs) const {
    return point(x - rhs.x, y - rhs.y);
  }
  point operator * (const flt k) const {
    return point(x * k, y * k);
  }
  point operator / (const flt k) const {
    return point(x / k, y / k);
  }
  point operator ~ () const {// counter clockwise rotate 90 degree
    return point(-y, x);
  }
  flt dot(const point &rhs) const {
    return x * rhs.x + y * rhs.y;
  }
  flt det(const point &rhs) const {
    return x * rhs.y - y * rhs.x;
  }
  flt norm2() const {
    return x * x + y * y;
  }
};

bool OnSeg(const point &A, const point &B, const point &O) {
  return (A - O).det(B - O) == 0 && (A - O).dot(B - O) <= 0;
}

int InPolygon(const std::vector<point> &P, const point &O) {
  int cnt = 0, n = P.size();
  for (int i = 0; i < n; ++i) {
    const point &A = P[i], &B = P[(i + 1) % n];
    if (OnSeg(A, B, O)) return 2;
    auto k = (B - A).det(O - A);
    auto d1 = A.y - O.y, d2 = B.y - O.y;
    cnt += (k > 0 && d1 <= 0 && d2 > 0);
    cnt -= (k < 0 && d2 <= 0 && d1 > 0);
  }
  return cnt != 0;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    std::vector<std::vector<point>> poly(n);
    std::vector<std::pair<int, int>> ps;
    for (int i = 0; i < n; ++i) {
      int m;
      scanf("%d", &m);
      poly[i].resize(m);
      for (int j = 0; j < m; ++j) {
        scanf("%lld%lld", &poly[i][j].x, &poly[i][j].y);
        ps.emplace_back(poly[i][j].y, i);
      }
    }
    std::sort(ps.begin(), ps.end());
    std::vector<bool> mark(n);
    std::vector<int> order;
    for (auto &e: ps) {
      if (mark[e.second]) continue;
      mark[e.second] = 1;
      order.push_back(e.second);
    }
    bool valid = true;
    for (int i = 1; i < n && valid; ++i) {
      const auto &p = poly[order[i - 1]];
      for (auto &pt: poly[order[i]]) {
        if (InPolygon(p, pt) != 1) {
          valid = false;
          break;
        }
      }
    }
    if (valid) puts("TAK");
    else puts("NIE");
  }
  return 0;
}

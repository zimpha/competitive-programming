#include <cstdio>
#include <vector>
#include <map>
#include <set>

int sgn(int x) {return x < 0 ? -1 : x > 0;}

struct point {
  int x, y;
  point(int x = 0, int y = 0): x(x), y(y) {}
  bool operator < (const point &rhs) const {
    return x < rhs.x || (x == rhs.x && y < rhs.y);
  }
  point operator + (const point &rhs) const {
    return point(x + rhs.x, y + rhs.y);
  }
  point operator - (const point &rhs) const {
    return point(x - rhs.x, y - rhs.y);
  }
  int det(const point &rhs) const {
    return x * rhs.y - y * rhs.x;
  }
  int dot(const point &rhs) const {
    return x * rhs.x + y * rhs.y;
  }
};

using poly_t = std::vector<point>;

bool OnSeg(const point &A, const point &B, const point &O) {
  return sgn((A - O).det(B - O)) == 0 && sgn((A - O).dot(B - O)) <= 0;
}

int InPolygon(const poly_t &P, const point &O) {
  int cnt = 0, n = P.size();
  for (int i = 0; i < n; ++i) {
    const point &A = P[i], &B = P[(i + 1) % n];
    if (OnSeg(A, B, O)) return 2;
    int k = sgn((B - A).det(O - A));
    int d1 = sgn(A.y - O.y), d2 = sgn(B.y - O.y);
    cnt += (k > 0 && d1 <= 0 && d2 > 0);
    cnt -= (k < 0 && d2 <= 0 && d1 > 0);
  }
  return cnt != 0;
}

int main() {
  int n;
  scanf("%d", &n);
  std::map<point, std::vector<point>> edges;
  for (int i = 0; i < n; ++i) {
    point a, b;
    scanf("%d%d%d%d", &a.x, &a.y, &b.x, &b.y);
    edges[a].push_back(b);
    edges[b].push_back(a);
  }
  std::set<point> mark;
  poly_t poly;
  point s = edges.begin()->first;
  for (int i = 0; i < n; ++i) {
    poly.push_back(s);
    mark.insert(s);
    for (auto &&e: edges[s]) {
      if (!mark.count(e)) {
        s = e;
        break;
      }
    }
  }
  scanf("%d%d", &s.x, &s.y);
  int res = InPolygon(poly, s);
  if (res == 0) puts("OUTSIDE");
  else if (res == 1) puts("INSIDE");
  else puts("BORDER");
  return 0;
}

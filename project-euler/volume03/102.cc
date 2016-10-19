#include <bits/stdc++.h>
using namespace std;

struct Point {
  int x, y;
  Point() {}
  Point(int x, int y): x(x), y(y) {}
  Point operator + (const Point &rhs) const {
    return Point(x + rhs.x, y + rhs.y);
  }
  Point operator - (const Point &rhs) const {
    return Point(x - rhs.x, y - rhs.y);
  }
  int det(const Point &rhs) const {
    return x * rhs.y - y * rhs.x;
  }
};

int sgn(int x) {
  return x < 0 ? -1 : x > 0;
}

bool run() {
  Point A, B, C, O(0, 0);
  scanf("%d,%d,%d,%d,%d,%d", &A.x, &A.y, &B.x, &B.y, &C.x, &C.y);
  int a = sgn((B - A).det(O - A));
  int b = sgn((C - B).det(O - B));
  int c = sgn((A - C).det(O - C));
  return (a < 0 && b < 0 && c < 0) || (a > 0 && b > 0 && c > 0);
}

int main() {
  freopen("triangles.txt", "r", stdin);
  int ret = 0;
  for (int i = 0; i < 1000; ++i) ret += run();
  printf("%d\n", ret);
  return 0;
}

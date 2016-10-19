#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

struct Point {
  int x, y;
  Point() {}
  Point(int a, int b): x(a), y(b) {}
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

LL run(int n) {
  vector<Point> xy;
  for (int x = 1; x < n; ++x) {
    for (int y = 1; y < n; ++y) {
      if (x * x + y * y < n * n) xy.push_back(Point(x, y));
    }
  }
  LL ret = 0;
  for (size_t i = 0; i < xy.size(); ++i) {
    for (size_t j = 0; j < xy.size(); ++j) {
      Point AB = xy[i] + xy[j];
      if (AB.det(xy[j]) < 0) ret += xy.size() + 2 * (n - 1);
    }
  }
  for (size_t i = 0; i < xy.size(); ++i) {
    Point AO = Point(-xy[i].x, xy[i].y);
    int a = 0, b = 0;
    for (size_t j = 0; j < xy.size(); ++j) {
      Point AB = Point(-xy[i].x - xy[j].x, xy[i].y + xy[j].y);
      a += AB.det(AO) < 0;
      b += AB.det(AO) > 0;
    }
    ret += a * b;
  }
  ret *= 4;
  ret += 4ll *(n - 1) * (n - 1) * xy.size();
  ret += 4ll * xy.size() * xy.size() * (n - 1);
  return ret;
}

int main() {
  cout << run(2) << endl;
  cout << run(3) << endl;
  cout << run(5) << endl;
  cout << run(105) << endl;
  return 0;
}

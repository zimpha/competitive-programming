#include <bits/stdc++.h>
using namespace std;
typedef pair<double, double> PII;

struct Point {
  int x, y;
  Point() {}
  Point(int _x, int _y): x(_x), y(_y) {}
  Point operator + (const Point &rhs) const {
    return Point(x + rhs.x, y + rhs.y);
  }
  Point operator - (const Point &rhs) const {
    return Point(x - rhs.x, y - rhs.y);
  }
  int det(const Point &rhs) const {
    return x * rhs.y - y * rhs.x;
  }
} A[5000], B[5000];

inline int gen(int s) {return 1ll * s * s % 50515093;}
inline int sgn(int x) {return x < 0 ? -1 : x > 0;}
PII inter(Point &A, Point &B, Point &C, Point &D) {
  int d1 = sgn((B - A).det(C - A)) * sgn((B - A).det(D - A));
  int d2 = sgn((D - C).det(A - C)) * sgn((D - C).det(B - C));
  if (d1 < 0 && d2 < 0) {
    Point O = B - A;
    int a = (D - C).det(C - A), b = (D - C).det(B - A);
    O.x *= a; O.y *= a;
    return PII(double(O.x + A.x * b) / b, double(O.y + A.y * b) / b);
  } else return PII(0, 0);
}

int run() {
  int s = 290797;
  for (int i = 0; i < 5000; ++i) {
    s = gen(s); A[i].x = s % 500;
    s = gen(s); A[i].y = s % 500;
    s = gen(s); B[i].x = s % 500;
    s = gen(s); B[i].y = s % 500;
  }
  int ret = 0;
  set<PII> S;
  for (int i = 0; i < 5000; ++i) {
    for (int j = i + 1; j < 5000; ++j) {
      S.insert(inter(A[i], B[i], A[j], B[j]));
    }
  }
  return S.size() - 1;
}

int main() {
  cout << run() << endl;
  return 0;
}

#include <bits/stdc++.h>

const double a = 7500, c = 5000;
const double b = sqrt(a * a - c * c);
const double PI = acos(-1.0);
const double lim = PI / 4;
typedef double flt;

struct point {
  flt x, y;
  point(flt a=0, flt b=0) : x(a), y(b) {}
  point operator *(const flt &k) const {return point(x*k,y*k);}
  point operator /(const flt &k) const {return point(x/k,y/k);}
  point operator -(const point &r) const {return point(x-r.x,y-r.y);}
  point operator +(const point &r) const {return point(x+r.x,y+r.y);}
  flt dot(const point &r) {return x*r.x+y*r.y;}
  flt det(const point &r) {return x*r.y-y*r.x;}
  flt sqr() {return x*x+y*y;}
  flt abs() {return hypot(x, y);}
};

point rot(const point &p, double cost, double sint) {
  double x = p.x, y = p.y;
  return point(x * cost - y * sint, x * sint + y * cost);
}

void cross(point A, double ra, point B, double rb, point &P, point &Q) {
  double d=(A-B).abs(),ct=(ra*ra+d*d-rb*rb)/(2*ra*d),st=sqrt(1.-ct*ct);
  point v=(B-A)/(B-A).abs()*ra;
  P=A+rot(v,ct,-st); Q=A+rot(v,ct,+st);
}

double get_angle(double x, double y) {
  const point F1(-c, 0), F2(c, 0);
  double r1 = 2 * a, r2 = (point(x, y) - F2).abs();
  point S1, S2;
  cross(F1, r1, point(x, y), r2, S1, S2);
  point v1 = S1 - F2, v2 = S2 - F2;
  return PI - acos(v1.dot(v2) / v2.abs() / v1.abs());
}

long long run() {
  long long ret = 0;
  for (int x = 0; ; ++x) {
    if (x <= a) {
      int upp = (int)floor(b * sqrt(a * a - x * x) / a + 1);
      int left = 0, right = 1e9;
      while (left < right) {
        int mid = (left + right + 1) >> 1;
        if (mid >= upp && get_angle(x, mid) <= lim) right = mid - 1;
        else left = mid;
      }
      ret += (left - upp + 1) * 2;
      if (x) ret += (left - upp + 1) * 2;
    } else {
      if (get_angle(x, 0) <= lim) break;
      int left = 0, right = 1e9;
      while (left < right) {
        int mid = (left + right + 1) >> 1;
        if (get_angle(x, mid) <= lim) right = mid - 1;
        else left = mid;
      }
      ret += (left * 2 + 1) * 2;
    }
  }
  return ret;
}

int main() {
  std::cout << run() << std::endl;
  return 0;
}

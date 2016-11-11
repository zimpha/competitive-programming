//http://math.stackexchange.com/questions/9819/area-of-a-spherical-triangle
#include <bits/stdc++.h>

const double eps = 1e-5;

struct point {
  int x, y, z;
};

point det(const point &a, const point &b) {
  return (point){a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
}

double dot(const point &a, const point &b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

int cmp(double a, double b) {
  double c = a - b;
  return c < -eps ? -1 : c > eps;
}

double run(int R) {
  std::vector<point> pt;
  for (int x = -R; x <= R; ++x) {
    for (int y = -R; y <= R; ++y) {
      for (int z = -R; z <= R; ++z) {
        if (x * x + y * y + z * z == R * R) {
          pt.push_back((point){x, y, z});
        }
      }
    }
  }
  double R2 = R * R, ret = 1e9;
  for (size_t i = 0; i < pt.size(); ++i) {
    point &A = pt[i];
    for (size_t j = i + 1; j < pt.size(); ++j) {
      point &B = pt[j];
      for (size_t k = j + 1; k < pt.size(); ++k) {
        point &C = pt[k];
        if (dot(det(A, B), C) == 0) continue;
        double a = acos(dot(B, C) / R2);
        double b = acos(dot(A, C) / R2);
        double c = acos(dot(A, B) / R2);
        double s = (a + b + c) / 2;
        double area = 4 * R2 * atan(sqrt(tan(s / 2) * tan((s - a) / 2) * tan((s - b) / 2) * tan((s - c) / 2)));
        ret = std::min(ret, area);
      }
    }
  }
  return ret;
}

int main() {
  std::cout.precision(20);
  std::cout << run(14) << std::endl;
  double ret = 0;
  for (int r = 1; r <= 50; ++r) {
    ret += run(r);
  }
  std::cout << ret << std::endl;
  return 0;
}

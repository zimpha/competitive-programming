#include <bits/stdc++.h>

double h1(double x, double y) {
  return 5000 - 0.005 * (x * x + y * y + x * y) + 12.5 * (x + y);
}

double h2(double x, double y) {
  return -(0.000001 * (x * x + y * y) - 0.0015 * (x + y) + 0.7);
}

double h(double x, double y) {
  return h1(x, y) * exp(h2(x, y));
}

double dis(double x1, double y1, double x2, double y2) {
  return hypot(x1 - x2, y1 - y2);
}

double run(int step) {
  const double fmin = 10396.4621932841041097408663;
  const double px = 624.6518830602000, py = 48.2528759250369;
  const double qx = 1536.0420725402400, qy = 873.0401231174810;
  double ret = dis(200, 200, px, py) + dis(qx, qy, 1400, 1400);
  double cx = 800, cy = 800;
  double pc = dis(cx, cy, px, py);
  double qc = dis(cx, cy, qx, qy);
  double pq = dis(px, py, qx, qy);
  double angle = acos((pc * pc + qc * qc - pq * pq) / (2 * pc * qc));
  double delta = angle / step;
  angle = asin(sqrt(pc * pc - (cy - py) * (cy - py)) / pc);
  angle = 3 * acos(-1.0) / 2 - angle;
  double x = px, y = py, r = pc;
  for (int it = 0; it < step; ++it) {
    angle += delta;
    double left = r - 1, right = r + 1;
    for (int i = 0; i < 100; ++i) {
      double mid = (left + right) * 0.5;
      double val = h(cx + mid * cos(angle), cy + mid * sin(angle));
      if (val < fmin) right = mid;
      else left = mid;
    }
    double rr = (left + right) * 0.5;
    double xx = cx + rr * cos(angle), yy = cy + rr * sin(angle);
    ret += dis(xx, yy, x, y);
    x = xx, y = yy, r = rr;
  }
  return ret;
}

int main() {
  std::cout.precision(20);
  std::cout << run(10000) << std::endl;
  return 0;
}

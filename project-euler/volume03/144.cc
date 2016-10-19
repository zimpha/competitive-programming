#include <bits/stdc++.h>
using namespace std;

int run() {
  double xs = 0, ys = 10.1;
  double xe = 1.4, ye = -9.6;
  int ret = 0;
  while (xe > .01 || xe < -.01 || ye < 0) {
    double ss = (ye - ys) / (xe - xs);
    double se = -4 * xe / ye;
    double ts = (ss - se) / (1 + ss * se);
    double sb = (se - ts) / (1 + ts * se);
    double ib = ye - sb * xe;
    double a = 4 + sb * sb;
    double b = 2 * sb * ib;
    double c = ib * ib - 100;
    double ans1 = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
    double ans2 = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);
    xs = xe; ys = ye;
    xe = abs(ans1 - xe) > abs(ans2 - xe) ? ans1 : ans2;
    ye = sb * xe + ib; ++ret;
  }
  return ret;
}

int main() {
  cout << run() << endl;
  return 0;
}

#include <bits/stdc++.h>
using namespace std;
const double PI = acos(-1.0), eps = 1e-9;
const double rad = PI / 180.0, deg = 180.0 / PI;
double sn[180], cs[180];

bool isInt(double x) {
  int y = round(x);
  return fabs(x - y) <= eps;
}

vector<int> add(int a, int b, int c, int d, int e, int f, int g, int h) {
  vector<int> r = {a, b, c, d, e, f, g, h};
  r = min(r, {c, d, e, f, g, h, a, b});
  r = min(r, {e, f, g, h, a, b, c, d});
  r = min(r, {g, h, a, b, c, d, e, f});
  r = min(r, {h, g, f, e, d, c, b, a});
  r = min(r, {f, e, d, c, b, a, h, g});
  r = min(r, {d, c, b, a, h, g, f, e});
  r = min(r, {b, a, h, g, f, e, d, c});
  return r;
}

// CAD, BAC, ABD, CBD, ACB, ACD, BCD, ADB
bool ok(int a, int b, int c, int d, int e, int f, int g, int h) {
  if (a + b + c + d + e + f + g + h != 360) return 0;
  double s1 = sn[a] * sn[c] * sn[e] * sn[g];
  double s2 = sn[b] * sn[d] * sn[f] * sn[h];
  return fabs(s1 - s2) <= eps;
}

int run() {
  for (int i = 0; i < 180; ++i) {
    sn[i] = sin(i * rad);
    cs[i] = cos(i * rad);
  }
  set<vector<int>> S;
  int ret = 0;
  for (int o = 1; o <= 90; ++o) {
    for (int a = 1; a < o; ++a) {
      for (int b = 1; b + o < 180 && b + a < 180; ++b) {
        for (int d = 1; d < o; ++d) {
          int c = 180 - b - o;
          int h = o - a, e = o - d;
          if (c + h + a + b != 180) continue;
          if (b + c + d + e != 180) continue;
          double x = sn[d] / sn[e];
          double y = sn[a] * sn[c] / sn[b] / sn[h];
          double z = sqrt(x * x + y * y - 2 * x * y * cs[o]);
          double gg = asin(x * sn[o] / z) * deg;
          if (!isInt(gg)) continue;
          int g = round(gg), f = 180 - o - g;
          if (g <= 0 || f <= 0 || g + f + e + d != 180) continue;
          if (a + f + g + h != 180) continue;
          if (ok(a, b, c, d, e, f, g, h)) {
            S.insert(add(a, b, c, d, e, f, g, h));
          }
          ++ret;
        }
      }
    }
  }
  //return ret;
  return S.size();
}

int main() {
  cout << run() << endl;
  return 0;
}

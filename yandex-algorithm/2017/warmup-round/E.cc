#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
#include <functional>
#include <algorithm>

const int N = 200 + 10;

int xw[N], yw[N];
int xr[N], yr[N];
int w, r;

using flt = double;

flt side(flt x1, flt y1, flt x2, flt y2, flt x3, flt y3) {
  return (x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1);
}

std::pair<flt, flt> get(flt x1, flt y1, flt x2, flt y2, flt x3, flt y3) {
  flt a1 = x2 - x1, b1 = y2 - y1, c1 = (a1 * a1 + b1 * b1) / 2;
  flt a2 = x3 - x1, b2 = y3 - y1, c2 = (a2 * a2 + b2 * b2) / 2;
  flt d = a1 * b2 - a2 * b1;
  return {x1 + (c1 * b2 - c2 * b1) / d, y1 + (a1 * c2 - a2 * c1) / d};
}

int main() {
  scanf("%d", &w);
  for (int i = 0; i < w; ++i) {
    scanf("%d%d", xw + i, yw + i);
  }
  scanf("%d", &r);
  for (int i = 0; i < r; ++i) {
    scanf("%d%d", xr + i, yr + i);
  }
  int ret = 0;
  for (int i = 0; i < w; ++i) {
    for (int j = 0; j < w; ++j) {
      if (i == j) continue;
      std::vector<flt> rw, u, v;
      flt dis = hypot(xw[j] - xw[i], yw[j] - yw[i]) / 2;
      flt xo = 0.5 * (xw[i] + xw[j]), yo = 0.5 * (yw[i] + yw[j]);
      for (int k = 0; k < w; ++k) {
        if (k == i || k == j) continue;
        if (side(xw[i], yw[i], xw[j], yw[j], xw[k], yw[k]) == 0) continue;
        auto e = get(xw[i], yw[i], xw[j], yw[j], xw[k], yw[k]);
        if (side(xw[i], yw[i], xw[j], yw[j], e.first, e.second) > 0) {
          rw.push_back(hypot(e.first - xw[i], e.second - yw[i]));
        }
      }
      int cnt = 0;
      for (int k = 0; k < r; ++k) {
        flt vv = side(xw[i], yw[i], xw[j], yw[j], xr[k], yr[k]);
        flt zz = hypot(xr[k] - xo, yr[k] - yo);
        auto e = get(xw[i], yw[i], xw[j], yw[j], xr[k], yr[k]);
        flt rad = hypot(e.first - xw[i], e.second - yw[i]);
        if (zz <= dis && vv >= 0) ++cnt;
        else {
          if (vv == 0) continue;
          if (zz <= dis) v.push_back(rad);
          if (vv > 0) u.push_back(rad);
        }
      }
      /*
      for (auto &&e: rw) printf("%.10f ", e);
      puts("");
      for (auto &&e: u) printf("%.10f ", e);
      puts("");
      */
      if (rw.empty()) continue;
      std::sort(rw.begin(), rw.end());
      std::sort(u.begin(), u.end(), std::greater<flt>());
      std::sort(v.begin(), v.end(), std::greater<flt>());
      for (auto &&e: rw) {
        while (v.size() && v.back() < e) v.pop_back();
        while (u.size() && u.back() < e) u.pop_back(), ++cnt;
        ret = std::max<int>(ret, cnt + v.size());
      }
      ret = std::max(ret, cnt);
    }
  }
  printf("%d\n", ret);
  return 0;
}

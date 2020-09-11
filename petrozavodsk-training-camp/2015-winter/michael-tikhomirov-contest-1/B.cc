#include <cmath>
#include <cstdio>
#include <vector>
#include <tuple>
#include <algorithm>

using flt = long double;

const flt eps = 1e-9;

/// argmin_z(az^2 + bz + c), z \in [zl, zr]
flt min_cost(flt a, flt b, flt c, flt l, flt r) {
  flt ret = std::min(a * l * l + b * l + c, a * r * r + b * r + c);
  if (fabs(a) > eps) {
    flt m = -b / (a * 2);
    if (l - eps <= m && m <= r + eps) {
      ret = std::min(ret, a * m * m + b * m + c);
    }
  }
  return ret;
}

int main() {
  int n, len, ts, energy;
  scanf("%d%d%d%d", &n, &len, &ts, &energy);
  std::vector<flt> x(n), m(n);
  for (int i = 0; i < n; ++i) {
    scanf("%Lf%Lf", &x[i], &m[i]);
    m[i] /= (flt)ts * ts * 2;
  }

  flt left = 1, right = len;
  for (int it = 0; it < 50; ++it) {
    flt mid = (left + right) * 0.5;
    std::vector<std::tuple<flt, int, int>> pos;
    int i = 0, j = 0, k = 0;
    while (i < n && j < n && k < n) {
      flt a = x[i], b = x[j] - mid * 0.5, c = x[k] - mid;
      if (a < b && a < c) {
        pos.emplace_back(a, i++, 0);
      } else if (b < a && b < c) {
        pos.emplace_back(std::max<flt>(b, 0), j++, 1);
      } else {
        c = std::max<flt>(c, 0);
        if (c < x[k] - mid * 0.5) {
          pos.emplace_back(c, k, 2);
        }
        k++;
      }
    }
    while (i < n && j < n) {
      flt a = x[i], b = x[j] - mid * 0.5;
      if (a < b) {
        pos.emplace_back(a, i++, 0);
      } else {
        pos.emplace_back(std::max<flt>(b, 0), j++, 1);
      }
    }
    for (; i < n; ++i) {
      pos.emplace_back(x[i], i, 0);
    }
    while (pos.size() && std::get<0>(pos.back()) + mid > len) {
      pos.pop_back();
    }
    pos.emplace_back(len - mid, n, 3);
    auto get_coefs = [&](int i, int ty, flt len) -> std::vector<flt> {
      if (ty == 0 || ty == -1) {
        return {0, 0, 0};
      } else {
        flt dx = ty == 2 ? len - x[i] : -x[i];
        return {m[i], 2.0 * dx * m[i], dx * dx * m[i]};
      }
    };

    // for each range of z, z <= x[i], z + mid * 0.5 <= x[j], z + d <= x[k]
    flt zl = 0;
    std::vector<flt> sum_coef(3, 0);
    std::vector<int> now_types(n, -1);
    bool valid = false;
    for (auto &e: pos) {
      flt zr = std::get<0>(e);
      int i = std::get<1>(e);
      int ty = std::get<2>(e);
      if (std::abs(zl - zr) > eps) {
        flt cost = min_cost(sum_coef[0], sum_coef[1], sum_coef[2], zl, zr);
        if (cost <= energy) {
          valid = true;
          break;
        }
      }
      if (ty != 3) {
        auto t_coef = get_coefs(i, now_types[i], mid);
        for (int i = 0; i < 3; ++i) sum_coef[i] -= t_coef[i];
        now_types[i] = ty;
        t_coef = get_coefs(i, now_types[i], mid);
        for (int i = 0; i < 3; ++i) sum_coef[i] += t_coef[i];
      }
      zl = zr;
    }
    if (valid) left = mid;
    else right = mid;
  }
  printf("%.10f\n", (double)left);
  return 0;
}
#include <bits/stdc++.h>
  
const double PI = acos(-1.0);

int len[100], n;

double get_angle(double r) {
  double ret = 0;
  for (int i = 0; i < n; ++i) {
    ret += asin(len[i] / 2.0 / r);
  }
  return ret;
}

double solve() {
  double left = len[n - 1] / 2., right = n * 2 - 3;
  if (get_angle(left) < PI) len[n - 1] = -len[n - 1];
  for (int i = 0; i < 50; ++i) {
    double mid = (left + right) * 0.5;
    double res = get_angle(mid);
    if (res <= 0 || res > PI) left = mid;
    else right = mid;
  }
  double res = 0;
  for (int i = 0; i < n; ++i) {
    res += sqrt(left * left - len[i] * len[i] / 4.0) * len[i];
  }
  if (len[n - 1] < 0) len[n - 1] = -len[n - 1];
  return res / 2;
}

using PDD = std::pair<double, double>;
PDD operator + (const PDD &a, const PDD &b) {
  return {a.first + b.first, a.second + b.second};
}

PDD dfs(int d, int sum, int last) {
  if (d == n) {
    if (sum) return {0., 0.};
    double now = 1;
    for (int i = 1, j = 1; i < n; ++i) {
      if (len[i] == len[i - 1]) ++j;
      else j = 1;
      now /= j;
    }
    double area = solve();
    return {area * now, now};
  }
  PDD res = {0., 0.};
  int rest = last * (n - d - 1);
  for (int i = last; i <= sum - rest; ++i) {
    len[d] = i;
    res = res + dfs(d + 1, sum - i, i);
  }
  return res;
}

double run(int upp) {
  double ret = 0;
  for (n = 3; n <= upp; ++n) {
    auto now = dfs(0, n * 2 - 3, 1);
    ret += now.first / now.second;
  }
  return ret;
}

int main() {
  std::cout.precision(20);
  std::cout << run(3) << std::endl;
  std::cout << run(4) << std::endl;
  std::cout << run(5) << std::endl;
  std::cout << run(10) << std::endl;
  std::cout << run(50) << std::endl;
  return 0;
}

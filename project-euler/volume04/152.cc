#include <bits/stdc++.h>
using namespace std;

const int ex[] = {11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79};
const double eps = 1e-12;

bool ok(int n) {
  for (int i = 0; i < 18; ++i) {
    if (n % ex[i] == 0) return false;
  }
  return true;
}

vector<int> a;
vector<double> ss;

int dfs(double now, int i, int n) {
  if (abs(now) < eps) return 1;
  if (i > n || now < -eps) return 0;
  if (ss[i] < now - eps) return 0;
  return dfs(now - 1.0 / (a[i] * a[i]), i + 1, n) + dfs(now, i + 1, n);
}

int run(int n) {
  for (int i = 3; i <= n; ++i) {
    if (ok(i)) a.push_back(i);
  }
  ss.assign(a.size() + 1, 0);
  for (int i = a.size() - 1; i >= 0; --i) {
    ss[i] = 1.0 / (a[i] * a[i]) + ss[i + 1];
  }
  n = a.size() - 1;
  double ex = 1.0 / (13 * 13) + 1.0 / (39 * 39) + 1.0 / (52 * 52);
  return dfs(.25, 0, n) + dfs(.25 - ex, 0, n);
}

int main() {
  //cout << run(45) << endl;
  cout << run(80) << endl;
  return 0;
}

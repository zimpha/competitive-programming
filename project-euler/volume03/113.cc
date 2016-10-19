#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

LL run(int n) {
  vector<vector<LL>> f, g;
  f.push_back(vector<LL>(10, 1));
  g.push_back(vector<LL>(10, 1));
  g[0][0] = f[0][0] = 0;
  LL ret = 0;
  for (int i = 1; i < n; ++i) {
    vector<LL> a(10, 0), b(10, 0);
    for (int x = 0; x < 10; ++x) {
      for (int y = 0; y < 10; ++y) {
        if (x <= y) a[y] += f.back()[x];
        if (x >= y) b[y] += g.back()[x];
      }
    }
    f.push_back(a);
    g.push_back(b);
  }
  for (int i = 1; i <= n; ++i) {
    for (int o = 0; o < 10; ++o) {
      ret += f[i - 1][o] + g[i - 1][o];
    }
    ret -= 9;
  }
  return ret;
}

int main() {
  cout << run(6) << endl;
  cout << run(10) << endl;
  cout << run(100) << endl;
  return 0;
}

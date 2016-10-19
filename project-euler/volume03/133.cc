#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

LL run(int n) {
  vector<int> pl, vs(n, 0);
  for (int i = 2; i < n; ++i) if (!vs[i]) {
    pl.push_back(i);
    for (int j = i; j < n; j += i) vs[j] = 1;
  }
  LL ret = 0;
  vector<int> mark(n * 10, 0);
  for (auto p: pl) {
    int m = p * 9;
    for (int x = 10 % m; ; ) {
      if (mark[x] == p) break; mark[x] = p;
      if (x == 1) break;
      LL y = 1;
      for (int _ = 0; _ < 10; ++_) {
        y = 1ll * y * x % m;
      }
      x = y;
    }
    if (mark[1] != p) {
      ret += p;
    }
  }
  return ret;
}

int main() {
  cout << run(100) << endl;
  cout << run(100000) << endl;
  return 0;
}

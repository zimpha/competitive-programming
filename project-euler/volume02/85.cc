#include <bits/stdc++.h>
using namespace std;

int calc(int n, int m) {
  int ret(0);
  for (int i = 1; i <= n; ++ i) {
    for (int j = 1; j <= m; ++ j) {
      ret += (n - i + 1) * (m - j + 1);
    }
  }
  return ret;
}

int sol(int tar) {
  int mx(tar), ret(-1);
  for (int n = 1; n <= tar; ++ n) {
    for (int m = 1; m <= n; ++ m) {
      int cnt = calc(n, m);
      if (m == 1 && cnt > tar) return ret;
      if (abs(cnt - tar) < mx) {
        mx = abs(cnt - tar);
        ret = n * m;
      }
      if (cnt > tar) break;
    }
  }
  return ret;
}

int main() {
  cout << sol(2000000) << endl;
  return 0;
}

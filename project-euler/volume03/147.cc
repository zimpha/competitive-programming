#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

int f(int n, int m) {
  if (n > m) swap(n, m);
  int ret = 0;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      ret += (n - i + 1) * (m - j + 1);
    }
  }
  n *= 2; m *= 2;
  for (int i = 0; i <= n; ++i) {
    for (int j = 0; j <= m; ++j) {
      if (i % 2 != j % 2) continue;
      for (int l = 1; i - l >= 0 && j - l >= 0; ++l) {
        ret += min(i - l, m - j);
      }
    }
  }
  return ret;
}

LL run(int n, int m) {
  if (n < m) swap(n, m);
  LL ret = 0;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      ret += f(i, j);
    }
  }
  return ret;
}

int main() {
  cout << run(3, 2) << endl;
  cout << run(47, 43) << endl;
  return 0;
}

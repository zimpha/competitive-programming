#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

LL run(int n, int m) {
  LL way[n + 1][m + 1];
  for (int i = 0; i <= n; ++i) {
    for (int j = 0; j <= m; ++j) {
      way[i][j] = 0;
    }
  }
  way[0][0] = 1;
  for (int a = 0; a <= n; ++a) {
    for (int b = 0; b <= m; ++b) if (a + b) {
      for (int i = 0; i + a <= n; ++i) {
        for (int j = 0; j + b <= m; ++j) {
          way[i + a][j + b] += way[i][j];
        }
      }
    }
  }
  return way[n][m];
}

int main() {
  cout << run(3, 1) << endl;
  cout << run(60, 40) << endl;
  return 0;
}

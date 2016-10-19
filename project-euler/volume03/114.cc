#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MAXN = 100;

LL C[MAXN][MAXN];

LL pm(LL a, LL n, LL r = 1) {
  for (; n; n >>= 1) {
    if (n & 1) r *= a;
    a *= a;
  }
  return r;
}

LL run(int n) {
  LL ret = 0;
  for (int m = 3; m <= n; ++m) {
    for (int k = 1; k * 3 <= m; ++k) {
      if (n - m - (k - 1) < 0) continue;
      ret += C[m - 2 * k - 1][k - 1] * C[n - m + 1][k];
    }
  }
  return ret + 1;
}

int main() {
  for (int i = 0; i < MAXN; ++i) {
    C[i][i] = C[i][0] = 1;
    for (int j = 1; j < i; ++j) {
      C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
    }
  }
  cout << run(7) << endl;
  cout << run(50) << endl;
  return 0;
}

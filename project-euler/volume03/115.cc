#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MAXN = 5000;

LL C[MAXN][MAXN];

LL f(int n, int m) {
  LL ret = 0;
  for (int s = m; s <= n; ++s) {
    for (int k = 1; k * m <= s; ++k) {
      if (n - s - (k - 1) < 0) continue;
      ret += C[s - (m - 1) * k - 1][k - 1] * C[n - s + 1][k];
      if (ret > 2000000) ret = 2000000;
    }
  }
  return ret + 1;
}

LL run(int m) {
  for (int n = 1; ; ++n) {
    if (f(n, m) > 1000000) return n;
  }
}

int main() {
  for (int i = 0; i < MAXN; ++i) {
    C[i][i] = C[i][0] = 1;
    for (int j = 1; j < i; ++j) {
      C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
      if (C[i][j] > 2000000) C[i][j] = 2000000;
    }
  }
  cout << run(3) << endl;
  cout << run(10) << endl;
  cout << run(50) << endl;
  return 0;
}

#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000 + 10;
typedef long long LL;

LL C[MAXN][MAXN];

LL f(int n, int m) {
  LL ret = 0;
  for (int k = 1; k * m <= n; ++k) {
    ret += C[n - k * m + k][k];
  }
  return ret;
}

LL run(int n) {
  return f(n, 2) + f(n, 3) + f(n, 4);
}

int main() {
  for (int i = 0; i < MAXN; ++i) {
    C[i][i] = C[i][0] = 1;
    for (int j = 1; j < i; ++j) {
      C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
    }
  }
  cout << run(5) << endl;
  cout << run(50) << endl;
  return 0;
}

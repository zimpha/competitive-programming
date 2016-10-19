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
  LL ret = 0;
  for (int r = 0; r * 2 <= n; ++r) {
    for (int g = 0; g * 3 <= n; ++g) {
      for (int b = 0; b * 4 <= n; ++b) {
        if (r * 2 + g * 3 + b * 4 > n) continue;
        ret += C[r][0] * C[g + r][g] * C[g + r + b][b] * 
               C[n - r * 2 - g * 3 - b * 4 + r + g + b][r + g + b];
      }
    }
  }
  return ret;
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

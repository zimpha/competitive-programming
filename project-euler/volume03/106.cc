#include <bits/stdc++.h>
using namespace std;

int C[20][20];

void run(int n) {
  for (int i = 0; i <= n; ++i) {
    C[i][0] = C[i][i] = 1;
    for (int j = 1; j < i; ++j) {
      C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
    }
  }
  int ret = 0;
  for (int a = 2; a <= n / 2; ++a) {
    ret += C[n][a] * C[n - a][a] / 2 - C[n][a * 2] * C[a * 2][a] / (a + 1);
  }
  cout << ret << endl;
}

int main() {
  run(4);
  run(7);
  run(12);
  return 0;
}

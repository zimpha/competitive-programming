#include <bits/stdc++.h>
using namespace std;
typedef long long LL;


int main() {
  LL C[20][20], ret = 0;
  for (int i = 0; i < 20; ++i) {
    C[i][0] = C[i][i] = 1;
    for (int j = 1; j < i; ++j) {
      C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
    }
  }
  for (int s = 0; s < 1048576; ++s) {
    int d[10]; memset(d, 0, sizeof(d));
    for (int i = 0, n = s; i < 10; ++i, n /= 4) d[i] = n % 4;
    if (accumulate(d, d + 10, 0) != 18) continue;
    for (int i = 1; i < 10; ++i) if (d[i]) {
      LL cnt = 1; --d[i];
      for (int j = 0, c = 0; j < 10; ++j) {
        cnt *= C[c + d[j]][d[j]];
        c += d[j];
      }
      ++d[i]; ret += cnt;
    }
  }
  cout << ret << endl;
  return 0;
}

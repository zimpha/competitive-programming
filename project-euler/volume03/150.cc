#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MAXN = 1000 + 10;
LL s[MAXN][MAXN];

int main() {
  int t = 0;
  for (int i = 1; i <= 1000; ++i) {
    for (int j = 1; j <= i; ++j) {
      t = (615949ll * t + 797807) % (1 << 20);
      s[i][j] = t - (1 << 19) + s[i][j - 1];
    }
  }
  LL ret = 0;
  for (int i = 1; i <= 1000; ++i) {
    for (int j = 1; j <= i; ++j) {
      LL tmp = 0;
      for (int k = i; k <= 1000; ++k) {
        tmp += s[k][j + k - i] - s[k][j - 1];
        ret = min(ret, tmp);
      }
    }
  }
  cout << ret << endl;
  return 0;
}

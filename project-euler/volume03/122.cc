#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200 + 10;
int val[MAXN], ret;

void dfs(int d, int lim) {
  if (val[d] == lim) {
    ret = d;
    return;
  }
  if (d >= ret) return;
  for (int i = 0; i <= d; ++i) {
    val[d + 1] = val[i] + val[d];
    if (val[d + 1] <= lim) dfs(d + 1, lim);
  }
}

int main() {
  int ans = 0;
  for (int i = 1; i <= 200; ++i) {
    ret = i - 1; val[0] = 1;
    dfs(0, i);
    ans += ret;
    if (i == 15) printf("%d\n", ret);
  }
  cout << ans << endl;
  return 0;
}

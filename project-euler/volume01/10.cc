#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MAXN = 2000000 + 10;
int pl[MAXN];

LL sol(int n) {
  LL ret(0);
  fill(pl, pl + n, 0);
  for (int i = 2; i < n; ++ i) if (!pl[i]) {
    ret += i;
    for (int j = i; j < n; j += i) pl[j] = 1;
  }
  return ret;
}

int main() {
  cout << sol(10) << endl;
  cout << sol(2000000) << endl;
  return 0;
}

#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

int sol(int n) {
  vector<int> phi(n + 1);
  for (int i = 0; i <= n; i ++) phi[i] = i;
  for (int i = 2; i <= n; ++ i) if (phi[i] == i) {
    for (int j = i; j <= n; j += i) {
      phi[j] = phi[j] / i * (i - 1);
    }
  }
  int ret = 1;
  for (int i = 2; i <= n; ++ i) {
    if ((LL)i * phi[ret] > (LL)ret * phi[i]) ret = i;
  }
  return ret;
}

int main() {
  cout << sol(10) << endl;
  cout << sol(1000000) << endl;
  return 0;
}

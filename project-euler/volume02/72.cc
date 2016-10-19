#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

LL sol(int n) {
  vector<int> phi(n + 1);
  for (int i = 0; i <= n; i ++) phi[i] = i;
  for (int i = 2; i <= n; ++ i) if (phi[i] == i) {
    for (int j = i; j <= n; j += i) {
      phi[j] = phi[j] / i * (i - 1);
    }
  }
  return accumulate(phi.begin(), phi.end(), 0LL) - 1;
}

int main() {
  cout << sol(8) << endl;
  cout << sol(1000000) << endl;
  return 0;
}

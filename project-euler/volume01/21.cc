#include <bits/stdc++.h>
using namespace std;

int sol(int n) {
  vector<int> dv(n + 1, 0);
  for (int i = 1; i <= n; ++ i) {
    for (int j = i + i; j <= n; j += i) {
      dv[j] += i;
    }
  }
  int ret(0);
  for (int i = 1; i <= n; ++ i) {
    if (dv[i] <= n && dv[dv[i]] == i && i != dv[i]) {
      ret += i; 
    }
  }
  return ret;
}

int main() {
  cout << sol(10000) << endl;
  return 0;
}

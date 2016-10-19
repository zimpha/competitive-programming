#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

int d(int n) {
  n %= 9; if (n == 0) n = 9;
  return n;
}

LL run(int n) {
  vector<vector<int>> fac(n);
  vector<int> mdrs(n);
  for (int i = 2; i < n; ++i) {
    for (int j = i + i; j < n; j += i) {
      fac[j].push_back(i);
    }
  }
  LL ret = 0;
  for (int i = 1; i < n; ++i) {
    mdrs[i] = d(i);
    for (int x : fac[i]) {
      mdrs[i] = max(mdrs[i], mdrs[i / x] + d(x));
    }
    ret += mdrs[i];
  }
  return ret - 1;
}

int main() {
  cout << run(1000000) << endl;
  return 0;
}

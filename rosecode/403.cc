#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

LL run(LL n) {
  int m = sqrt(n) + 10;
  vector<int> mu(m, 0);
  for (int i = 1; i < m; ++i) {
    mu[i] += i == 1;
    for (int j = i + i; j < m; j += i) {
      mu[j] -= mu[i];
    }
  }
  LL ret = 0;
  for (int i = 1; i < m; ++i) {
    ret += mu[i] * (n / i / i);
  }
  return ret;
}

int main() {
  cout << run(12) << endl;
  cout << run(200000000000ll) << endl;
  cout << run(123456789123456789ll) << endl;
  return 0;
}

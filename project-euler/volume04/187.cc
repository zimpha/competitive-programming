#include <bits/stdc++.h>
using namespace std;
const int N = 100000000;

int p[N], pi[N], m;

int run(int n) {
  for (int i = 2; i < n; ++i) pi[i] = 1; m = 0;
  for (int i = 2; i < n; ++i) {
    if (pi[i]) p[m++] = i;
    for (int j = 0; j < m && p[j] * i < n; ++j) {
      pi[i * p[j]] = 0;
      if (i % p[j] == 0) break;
    }
  }
  for (int i = 2; i < n; ++i) pi[i] += pi[i - 1];
  int ret = 0;
  for (int i = 0; p[i] * p[i] < n; ++i) {
    ret += pi[n / p[i]] - pi[p[i]] + 1;
  }
  return ret;
}

int main() {
  cout << run(30) << endl;
  cout << run(100000000) << endl;
  return 0;
}

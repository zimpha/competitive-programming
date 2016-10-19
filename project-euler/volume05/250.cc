#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL M = 10000000000000000ll;
const int S = 250;

LL f[S], g[S];

int pm(int a, int n) {
  int r = 1;
  for (a %= S; n; n >>= 1) {
    if (n & 1) r = r * a % S;
    a = a * a % S;
  }
  return r;
}

int main() {
  f[0] = 1;
  for (int i = 1; i <= 250250; ++i) {
    int o = pm(i, i);
    for (int j = 0; j < S; ++j) g[j] = f[j];
    for (int j = 0; j < S; ++j) if (f[j]) {
      g[(j + o) % S] += f[j];
    }
    for (int j = 0; j < S; ++j) f[j] = g[j] % M;
  }
  cout << f[0] - 1 << endl;
  return 0; 
}

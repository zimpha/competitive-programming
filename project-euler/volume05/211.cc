#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 64000000;
LL sg[N];

LL run(int n) {
  for (int i = 0; i < n; ++i) sg[i] = 0;
  for (int i = 1; i < n; ++i) {
    for (int j = i; j < n; j += i) {
      sg[j] += 1ll * i * i;
    }
  }
  LL ret = 0;
  for (int i = 1; i < n; ++i) {
    LL x = sqrt(sg[i]);
    if (x * x == sg[i]) ret += i;
  }
  return ret;
}

int main() {
  cout << run(N) << endl;
  return 0;
}

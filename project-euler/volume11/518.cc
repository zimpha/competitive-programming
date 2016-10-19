#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 100000000;
int vs[N], p[N], m;

void sieve() {
  m = 0; vs[0] = vs[1] = 1;
  for (int i = 2; i < N; ++i) {
    if (!vs[i]) p[m++] = i;
    for (int j = 0; j < m && p[j] <= N / i; ++j) {
      vs[i * p[j]] = 1;
      if (i % p[j] == 0) break;
    }
  }
}

LL run(LL n) {
  LL ret = 0;
  for (int k = 1; k <= n; ++k) {
    int s = n / k;
    for (int y = 1; y * y <= s; ++y) if (!vs[k * y * y - 1]) {
      for (int x = y + 1; x * x <= s; ++x) if (!vs[k * x * x - 1]) {
        if (__gcd(x, y) != 1) continue;
        if (!vs[k * x * y - 1]) {
          ret += k * (x * x + y * y + x * y) - 3;
        }
      }
    }
  }
  return ret;
}

int main() {
  sieve();
  cout << run(100) << endl;
  cout << run(100000000) << endl;
  return 0;
}

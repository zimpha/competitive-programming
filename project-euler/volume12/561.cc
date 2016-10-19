#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

// E(904961, 4k) = #[2k]
// E(904961, 4k-1) = #[(2k)^m]
// 1 <= k <= n / 4
LL run(LL n) {
  n /= 4;
  LL ret = 0, p = 1;
  const int m = 904961;
  for (int i = 0; p <= n; ++i, p <<= 1) {
    LL cnt = n / p - n / p / 2;
    ret += cnt * (i + 1);
    ret += cnt * (i + 1) * m;
  }
  return ret;
}

int main() {
  cout << run(8) << endl;
  cout << run(1000000000000ll) << endl;
  return 0;
}

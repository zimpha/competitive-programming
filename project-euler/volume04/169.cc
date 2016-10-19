#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef __int128 i128;

map<i128, i128> mp;

void out(i128 n) {
  LL x = n % LL(1e18), y = n / LL(1e18);
  if (y != 0) printf("%lld%018lld\n", y, x);
  else printf("%lld\n", x);
}

i128 run(i128 n) {
  if (n == 0) return 1;
  if (mp.count(n)) return mp[n];
  if (n % 2 == 0) return mp[n] = run(n / 2) + run(n / 2 - 1);
  else return mp[n] = run(n / 2);
}

int main() {
  out(run(1));
  out(run(2));
  out(run(3));
  out(run(4));
  out(run(5));
  out(run(6));
  out(run(7));
  out(run(8));
  out(run(9));
  out(run(10));
  i128 n = 1;
  for (int i = 0; i < 25; ++i) n *= 10;
  out(run(n));
  return 0;
}

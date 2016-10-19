#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int M5 = 3125, M2 = 32;

LL A5[M5], A2[M2];

void init() {
  A2[0] = A5[0] = 1;
  for (int i = 1; i < M5; ++i) {
    if (i % 5 == 0) A5[i] = A5[i - 1];
    else A5[i] = A5[i - 1] * i % M5;
  }
  for (int i = 1; i < M2; ++i) {
    if (i % 2 == 0) A2[i] = A2[i - 1];
    else A2[i] = A2[i - 1] * i % M2;
  }
}

LL pm(LL a, LL n, LL m) {
  LL r = 1;
  for (a %= m; n; n >>= 1) {
    if (n & 1) r = r * a % m;
    a = a * a % m;
  }
  return r;
}
void exgcd(LL a,LL b,LL &g,LL &x,LL &y) {
  if (!b) x=1,y=0,g=a;
  else {exgcd(b,a%b,g,y,x);y-=x*(a/b);}
}

LL mod_inv(LL a,LL m) {
  LL d,x,y; exgcd(a,m,d,x,y);
  return d==1?(x%m+m)%m:-1;
}

LL run(LL n) {
  LL v2 = 0, v5 = 0;
  for (LL p = 2; p <= n; p *= 2) v2 += n / p;
  for (LL p = 5; p <= n; p *= 5) v5 += n / p;
  LL x5 = pm(mod_inv(2, M5), v5, M5);
  LL x2 = pm(mod_inv(5, M2), v5, M2) * pm(2, v2 - v5, M2) % M2;
  for (LL p = 1; p <= n; p *= 5) {
    x5 = x5 * A5[(n / p) % M5] % M5;
    if ((n / p / M5) & 1) x5 = (M5 - x5) % M5;
  }
  for (LL p = 1; p <= n; p *= 2) {
    x2 = x2 * A2[(n / p) % M2] % M2;
    if ((n / p / M2) & 1) x2 = (M2 - x2) % M2;
  }
  return (x2 * mod_inv(M5, M2) * M5 + x5 * mod_inv(M2, M5) * M2) % (M2 * M5);
}

int main() {
  init();
  cout << run(9) << endl;
  cout << run(10) << endl;
  cout << run(20) << endl;
  cout << run(1000000000000ll) << endl;
  return 0;
}

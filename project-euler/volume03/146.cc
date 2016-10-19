#include <bits/stdc++.h>
using namespace std;
typedef __int128 i128;
typedef long long LL;

inline LL mul_mod(i128 a, i128 b, LL m) {
  return a * b % m;
}

LL pm(LL a, LL n, LL m) {
  LL r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = mul_mod(r, a, m);
    a = mul_mod(a, a, m);
  }
  return r;
}

bool test(LL n, LL b) {
  LL m=n-1,cnt=0;
  while(~m&1) m>>=1,cnt++;
  LL r=pm(b,m,n);
  if (r==1||r==n-1) return true;
  for (cnt--;cnt>=0;cnt--) {
    r=mul_mod(r,r,n);
    if (r==n-1) return true;
  }
  return false;
}
const int BASE[12]={2,3,5,7,11,13,17,19,23,29,31,37};
bool isPrime(LL n) {
  if (n<2) return false;
  if (n<4) return true;
  if (n==3215031751LL) return false;
  for (int i=0;i<12&&BASE[i]<n;++i) {
    if (!test(n,BASE[i])) return false;
  }
  return true;
}

LL run(int n) {
  LL ret = 0;
  for (int i = 10; i <= n; i += 10) {
    LL s = 1ll * i * i;
    if (s % 3 != 1 || s % 9 == 0 || s % 13 == 0 || s % 27 == 0) continue;
    if (s % 7 != 2 && s % 7 != 3) continue;
    if (isPrime(s + 1) && isPrime(s + 3) && isPrime(s + 7) && isPrime(s + 9) &&
        isPrime(s + 13) && isPrime(s + 27) && !isPrime(s + 19) && !isPrime(s + 21)) ret += i;
  }
  return ret;
}

int main() {
  cout << run(1000000) << endl;
  cout << run(150000000) << endl;
  return 0;
}

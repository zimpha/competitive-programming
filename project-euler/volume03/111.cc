#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int M[] = {8, 9, 8, 9, 9, 9, 9, 9, 8, 9};
LL pw[20];

bool isPrime(LL n) {
  for (int i = 2; 1ll * i * i <= n; ++i) {
    if (n % i == 0) return false;
  }
  return true;
}

LL solve(int d) {
  LL ret = 0;
  for (int msk = 0; msk < 1024; ++msk) {
  if (__builtin_popcount(msk) != M[d]) continue;
    LL base = 0; vector<int> p;
    for (int i = 0; i < 10; ++i) {
      if (msk >> i & 1) base += pw[i] * d;
      else p.push_back(i);
    }
    if (p.size() == 1) {
      for (int i = 0; i < 10; ++i) {
        LL r = base + pw[p[0]] * i;
        if (r >= 1000000000 && isPrime(r)) {
          ret += r;
        }
      }
    } else {
      for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
          LL r = base + pw[p[0]] * i + pw[p[1]] * j;
          if (r >= 1000000000 && isPrime(r)) {
            ret += r;
          }
        }
      }
    }
  }
  return ret;
}

int main() {
  for (int i = pw[0] = 1; i < 20; ++i) pw[i] = pw[i - 1] * 10;
  LL ret = 0;
  for (int i = 0; i < 10; ++i) {
    ret += solve(i);
  }
  cout << ret << endl;
  return 0;
}

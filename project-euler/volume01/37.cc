#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

bool isPrime(LL n) {
  if (n < 2) return 0;
  if (n <= 3) return 1;
  if (n % 2 == 0) return 0;
  for (LL i = 3; i * i <= n; i += 2) {
    if (n % i == 0) return 0;
  }
  return 1;
}

int cnt(0), ret(0);

void sol(LL s, LL p, LL n = 0) {
  const int d[] = {1, 2, 3, 5, 7, 9};
  if (s / 10) {
    for (n = s; n; n /= 10) {
      if (!isPrime(n)) break;
    }
    if (!n) {
      ret += s, ++ cnt;
      cout << s << endl;
    }
    if (cnt == 11) return;
  }
  for (int i = 0; i < 6; ++ i) {
    LL x = s + p * d[i];
    if (isPrime(x)) sol(x, p * 10);
  }
}

int main() {
  sol(0, 1);
  cout << ret << endl;
  return 0;
}

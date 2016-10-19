#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

bool isPrime(LL n) {
  if (n < 2) return 0;
  if (n < 4) return 1;
  if (n % 2 == 0) return 0;
  for (LL i = 3; i * i <= n; i ++) {
    if (n % i == 0) return 0;
  }
  return 1;
}

int sol() {
  int tot(1), p(0);
  for (LL n = 2; ; ++ n) {
    tot += 4;
    p += isPrime((2 * n - 1) * (2 * n - 1));
    p += isPrime(4 * (n - 1) * (n - 1) + 1);
    p += isPrime(4 * n * n - 6 * n + 3);
    p += isPrime(4 * n * n - 10 * n + 7);
    if (p * 10 < tot) return n * 2 - 1;
  }
  return -1;
}

int main() {
  cout << sol() << endl;
  return 0;
}

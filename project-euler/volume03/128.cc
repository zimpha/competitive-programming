#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

bool isPrime(LL n) {
  if (n < 2) return 0;
  if (n <= 3) return 1;
  if (n % 2 == 0) return 0;
  for (int i = 3; i * i <= n; i += 2) {
    if (n % i == 0) return 0;
  }
  return 1;
}

LL run(int cnt) {
  for (LL n = 1; cnt; ++n) {
    if (isPrime(n * 6 - 1) && isPrime(n * 6 + 1) && isPrime(n * 12 + 5)) {
      if (--cnt == 1) return n * n * 3 - n * 3 + 2;
    }
    if (isPrime(n * 6 + 5) && isPrime(n * 6 - 1) && isPrime(n * 12 - 7) && n != 1) {
      if (--cnt == 1) return n * n * 3 + n * 3 + 1;
    }
  }
  return -1;
}

int main() {
  cout << run(10) << endl;
  cout << run(2000) << endl;
  return 0;
}

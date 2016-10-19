#include <bits/stdc++.h>
using namespace std;

int A(int n) {
  if (__gcd(n, 10) != 1) return 0;
  for (int x = 1, k = 1; x; ) {
    x = (x * 10 + 1) % n; ++k;
    if (x == 0) return k;
  }
  return -1;
}

bool isPrime(int n) {
  if (n < 2) return false;
  if (n <= 3) return true;
  if (n % 2 == 0) return false;
  for (int i = 3; i * i <= n; i += 2) {
    if (n % i == 0) return false;
  }
  return true;
}

int run(int cnt) {
  int ret = 0;
  for (int n = 3; cnt; n += 2) {
    if (n % 5 == 0 || isPrime(n)) continue;
    int len = A(n);
    if ((n - 1) % len == 0) {
      --cnt;
      ret += n;
    }
  }
  return ret;
}

int main() {
  cout << run(5) << endl;
  cout << run(25) << endl;
  return 0;
}

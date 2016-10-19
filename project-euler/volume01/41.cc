#include <bits/stdc++.h>
using namespace std;

bool isPrime(int n) {
  if (n % 2 == 0) return 0;
  for (int i = 3; i * i <= n; i += 2) {
    if (n % i == 0) return 0;
  }
  return 1;
}

int sol(int n) {
  string s = "123456789";
  int ret(0);
  do {
    int x(0);
    for (int i = 0; i < n; ++ i) x = x * 10 + s[i] - '0';
    if (isPrime(x)) ret = x;
  } while (next_permutation(s.begin(), s.begin() + n));
  return ret;
}

int main() {
  int mx(0);
  for (int n = 9; n >= 2; -- n) {
    mx = sol(n);
    if (mx) break;
  }
  cout << mx << endl;
  return 0;
}

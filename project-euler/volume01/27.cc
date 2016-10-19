#include <bits/stdc++.h>
using namespace std;

bool isprime(int n) {
  if (n <= 1) return 0;
  if (n <= 3) return 1;
  if (n % 2 == 0) return 0;
  for (int i = 3; i * i <= n; i += 2) {
    if (n % i == 0) return 0;
  }
  return 1;
}

int sol(int a, int b) {
  for (int n = 0; ; ++ n) {
    if (!isprime(n * n + n * a + b)) return n;
  }
  return -1;
}

int main() {
  int mx(-1), ret(0);
  for (int a = -999; a <= 999; ++ a) {
    for (int b = -999; b <= 999; ++ b) {
      int cnt = sol(a, b);
      if (cnt > mx) mx = cnt, ret = a * b;
    }
  }
  cout << ret << endl;
  return 0;
}

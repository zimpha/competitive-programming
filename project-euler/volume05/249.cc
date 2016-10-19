#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL M = 10000000000000000ll;
const int MAXN = 1600000;

LL f[MAXN], g[MAXN];

bool isPrime(int n) {
  if (n < 2) return 0;
  if (n <= 3) return 1;
  if (n % 2 == 0) return 0;
  for (int i = 3; i * i <= n; i += 2) {
    if (n % i == 0) return 0;
  }
  return 1;
}

int main() {
  int sum = 0;
  f[0] = 1;
  for (int i = 2; i < 5000; ++i) if (isPrime(i)) {
    sum += i;
    for (int j = sum; j >= i; --j) {
      f[j] += f[j - i]; f[j] %= M;
    }
  }
  cout << sum << endl;
  LL ret = 0;
  for (int i = 2; i <= sum; ++i) {
    if (isPrime(i)) ret += f[i];
    ret %= M;
  }
  cout << ret << endl;
  return 0;
}

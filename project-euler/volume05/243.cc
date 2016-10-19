#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

vector<int> phi;

void sieve(int n) {
  phi.resize(n);
  for (int i = 0; i < n; ++ i) phi[i] = i;
  for (int i = 2; i < n; ++ i) if (i == phi[i]) {
    for (int j = i; j < n; j += i) {
      phi[j] = phi[j] / i * (i - 1);
    }
  }
}

LL getPhi(LL n) {
  if (n < phi.size()) return phi[n];
  LL r(n);
  for (LL i = 2; i * i <= n; ++ i) {
    if (n % i == 0) {
      r = r / i * (i - 1);
      while (n % i == 0) n /= i;
    }
  }
  if (n > 1) r = r / n * (n - 1);
  return r;
}

LL sol(LL a, LL b) {
  vector<int> can;
  for (size_t i = 2; i < phi.size(); ++ i) {
    if (i == phi[i] + 1) can.push_back(i);
  }
  LL d(1);
  for (size_t i = 0; i < can.size(); ++ i) {
    int t = can[i];
    for (int k = 1; k < t; ++ k) {
      LL x = getPhi(d * k);
      LL y = d * k - 1;
      if (x * b < y * a) return d * k;
    }
    d = d * t;
  }
  return -1;
}

int main() {
  int n = 1000000;
  sieve(n);
  cout << sol(4, 10) << endl;
  cout << sol(15499, 94744) << endl;
  return 0;
}

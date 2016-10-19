#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 10000000;
LL phi[N], p[N], m;

map<LL, LL> Phi;

LL get_phi(LL n) {
  if (n < N) return phi[n];
  LL &r = Phi[n]; if (r) return r;
  r = n * (n + 1) / 2;
  for (int i = 2, j; i <= n; i = j + 1) {
    j = n / (n / i);
    r -= get_phi(n / i) * (j - i + 1);
  }
  return r;
}

void sieve() {
  phi[1] = 1; m = 0;
  for (int i = 2; i < N; ++i) {
    if (!phi[i]) p[m++] = i, phi[i] = i - 1;
    for (int j = 0; j < m && p[j] <= N / i; ++j) {
      if (i % p[j] == 0) {
        phi[i * p[j]] = phi[i] * p[j]; break;
      } else phi[i * p[j]] = phi[i] * (p[j] - 1);
    }
  }
  for (int i = 1; i < N; ++i) phi[i] += phi[i - 1];
}

map<LL, LL> g;

LL run(LL n) {
  LL &r = g[n]; if (r) return r;
  r = get_phi(n);
  for (LL p = 1; p <= n; p <<= 1) {
    r -= p * run(n / p / 2);
  }
  return r;
}

int main() {
  sieve();
  cout << run(100) << endl;
  cout << run(500000000) << endl;
  return 0;
}

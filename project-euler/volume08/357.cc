#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 100000000;
int pl[N], m;
bool vs[N + 1], mu[N + 1];

void sieve() {
  mu[1] = 1;
  for (int i = 2; i < N; ++i) {
    if (!vs[i]) pl[m++] = i, mu[i] = 1;
    for (int j = 0; j < m && pl[j] <= N / i; ++j) {
      vs[pl[j] * i] = 1;
      if (i % pl[j] == 0) {mu[i * pl[j]] = 0; break;}
      else mu[i * pl[j]] = 1;
    }
  }
}

bool ok(int n) {
  if (!vs[n]) return n <= 2;
  for (int i = 1; i * i <= n; ++i) if (n % i == 0) {
    if (vs[i + n / i]) return 0;
  }
  return 1;
}

LL run(int n) {
  LL ret = 0;
  for (int i = 1; i < n; ++i) if (mu[i]) {
    if (ok(i)) ret += i;
  }
  return ret;
}

int main() {
  sieve();
  cout << run(100000000) << endl;
}

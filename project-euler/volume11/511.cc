#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MOD = 1e9, MAXN = 5000;

void mul(LL A[], LL B[], int m) {
  static LL C[MAXN];
  for (int i = 0; i < m; ++ i) {
    C[i] = 0;
    for (int j = 0; j < m; ++ j) {
      C[i] += A[j] * B[(i - j + m) % m] % MOD;
    }
    C[i] %= MOD;
  }
  for (int i = 0; i < m; ++ i) A[i] = C[i];
}

void solve(LL n, int k) {
  static LL base[MAXN], R[MAXN];
  for (int i = 0; i < k; ++ i) R[i] = base[i] = 0;
  for (LL d = 1; d * d <= n; ++ d) {
    if (n % d == 0) {
      base[d % k] ++;
      if (d * d != n) base[n / d % k] ++;
    }
  }
  R[n % k] = 1;
  for (; n; n >>= 1) {
    if (n & 1) mul(R, base, k);
    mul(base, base, k);
  }
  cout << R[0] << endl;
}

int main() {
  solve(3, 4);
  solve(4, 11);
  solve(1111, 24);
  solve(1234567898765ll,4321);
  return 0;
}
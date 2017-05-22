#include <bits/stdc++.h>

const int N = 5000000 + 10, mod = 1e9 + 7;

long phi[N], d[N], f[N];

int main() {
  for (int i = 1; i < N; ++i) {
    phi[i] = i;
    for (int j = i; j < N; j += i) {
      d[j] += 1;
    }
  }
  for (int i = 2; i < N; ++i) if (phi[i] == i) {
    for (int j = i; j < N; j += i) phi[j] = phi[j] / i * (i - 1);
  }
  for (int i = 1; i < N; ++i) {
    f[i] = phi[i] * d[i];
  }
  long ret = 0;
  for (int k = 1; k <= 20172017; ++k) {
    int p = 1;
    for (int n = k; n; n /= 10) p *= n % 10;
    ret += f[p];
    ret %= mod;
  }
  std::cout << ret << std::endl;
  return 0;
}

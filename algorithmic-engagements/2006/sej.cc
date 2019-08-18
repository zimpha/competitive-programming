#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>

int pow_mod(int a, int n, int mod) {
  int r = 1;
  for (a %= mod; n; n >>= 1) {
    if (n & 1) r = r * a % mod;
    a = a * a % mod;
  }
  return r;
}

int main() {
  int n, p;
  scanf("%d%d", &n, &p);
  std::vector<std::vector<int>> a(n, std::vector<int>(n));
  std::vector<int> knob(n), bolt(n), x(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &knob[i]);
  }
  for (int i = 0; i < n; ++i) {
    scanf("%d", &bolt[i]);
    x[i] = (p - bolt[i]) % p;
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      scanf("%d", &a[j][i]);
    }
  }
  for (int k = 0, i, j, s; k < n; ++k){
    for (s=k, i = k + 1; i < n; ++i) {
      if (a[i][k] > a[s][k]) s = i;
    }
    assert(a[s][k]);
    if (s != k){
      std::swap(x[s], x[k]);
      for (i = k; i < n; ++i) {
        std::swap(a[s][i], a[k][i]);
      }
    }
    int iv = pow_mod(a[k][k], p - 2, p);
    for (j = k + 1; j < n; ++j){
      int t = (p - a[j][k]) * iv % p;
      x[j] = (x[j] + x[k] * t) % p;
      for (i = k + 1; i < n; ++i) {
        a[j][i] = (a[j][i] + t * a[k][i]) % p;
      }
    }
  }
  for (int i = n - 1; i >= 0; --i){
    x[i] = x[i] * pow_mod(a[i][i], p - 2, p) % p;
    for (int j = 0; j < i; ++j) {
      x[j] = (x[j] - a[j][i] * x[i] % p + p) % p;
    }
  }
  for (int i = 0; i < n; ++i) {
    knob[i] = (knob[i] + x[i]) % p;
    if (i) putchar(' ');
    printf("%d", knob[i]);
  }
  puts("");
  return 0;
}

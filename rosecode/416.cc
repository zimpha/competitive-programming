#include <cstdio>
#include <vector>

using int64 = long long;

const int N = 1000;

std::vector<int> dv[N];
int phi[N], p[N];
int m;

int64 pow_mod(int64 a, int64 n, int64 mod) {
  int64 r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % mod;
    a = a * a % mod;
  }
  return r;
}

bool test(int g, int n, int phi) {
  for (auto &&p: dv[phi]) {
    if (pow_mod(g, phi / p, n) == 1) return false;
  }
  return true;
}

int root(int n) {
  for (int g = 1; ; ++g) {
    if (test(g, n, phi[n])) return g;
  }
  return -1;
}

int gao(int n) {
  int g = root(n);
  printf("n = %d, g = %d: ", n, g);
  int cnt = 0, total = 0;
  for (int i = 1; i <= (n - 1) / 2; ++i) {
    if (pow_mod(i, (n - 1) / 2, n) == 1) ++cnt;
    total += pow_mod(i, (n - 1) / 2, n);
    total %= n;
  }
  int r = 1;
  for (int i = 1; i <= n / 2; ++i) r = r * i % n;
  printf("(%d, %d, %d), %d\n", total, cnt, (n + total * 2 - 1) / 4, r);
  return r;
}

int main() {
  for (int i = 0; i < N; ++i) phi[i] = i;
  for (int i = 2; i < N; ++i) if (!p[i]) {
    p[m++] = i;
    for (int j = i; j < N; j += i) {
      p[j] = 1;
      phi[j] = phi[j] / i * (i - 1);
      dv[j].push_back(i);
    }
  }
  for (int i = 0; i < m; ++i) {
    if (p[i] % 4 == 3) {
      gao(p[i]);
    }
  }
  return 0;
}

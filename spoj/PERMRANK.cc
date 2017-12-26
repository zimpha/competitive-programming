#include <cstdio>

using int64 = long long;

const int N = 30;

int64 fact[N];

int bit[N], n;

void add(int x, int v) {
  for (; x <= n; x += ~x & x + 1) bit[x] += v;
}

int get(int x, int r = 0) {
  for (; x >= 0; x -= ~x & x + 1) r += bit[x];
  return r;
}

int main() {
  fact[0] = 1;
  for (int i = 1; i < N; ++i) fact[i] = i * fact[i - 1];
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    scanf("%d", &n);
    for (int i = 0; i <= n; ++i) bit[i] = 0;
    int64 ret = 0;
    for (int i = 0; i < n; ++i) {
      int x;
      scanf("%d", &x);
      ret += fact[n - i - 1] * (x - get(x) - 1);
      add(x, 1);
    }
    printf("%lld\n", ret + 1);
  }
  return 0;
}

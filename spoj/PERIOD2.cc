#include <cstdio>

using int64 = long long;

const int N = 1e7;

bool mark[N];
int p[N / 10], m;

void prepare() {
  for (int i = 2; i < N; ++i) {
    if (!mark[i]) p[m++] = i;
    for (int j = 0, u = (N - 1) / i; j < m && p[j] <= u; ++j) {
      mark[i * p[j]] = 1;
      if (i % p[j] == 0) break;
    }
  }
}

int main() {
  prepare();
  int T;
  scanf("%d", &T);
  for (int cas = 0; cas < T; ++cas) {
    int n, mod;
    scanf("%d%d", &n, &mod);
    int ret = 1;
    for (int i = 0; i < m && p[i] <= n; ++i) {
      for (int u = n; u >= p[i]; u /= p[i]) ret = (int64)ret * p[i] % mod;
    }
    printf("%d\n", ret);
  }
  return 0;
}

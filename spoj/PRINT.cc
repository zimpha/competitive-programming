#include <cstdio>

using int64 = long long;

const int S = 50000, N = 1e6 + 10;

int p[S], m;
bool mark[N];

void prepare() {
  for (int i = 2; i < S; ++i) if (!p[i]) {
    p[m++] = i;
    for (int j = i + i; j < S; j += i) p[j] = 1;
  }
}

int main() {
  prepare();
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int64 L, U;
    scanf("%lld%lld", &L, &U);
    int n = U - L;
    for (int i = 0; i <= n; ++i) mark[i] = 0;
    for (int i = 0; i < m; ++i) {
      int64 x = (L + p[i] - 1) / p[i] * p[i];
      if (x == p[i]) x += p[i];
      for (; x <= U; x += p[i]) mark[x - L] = 1;
    }
    for (int i = 0; i <= n; ++i) if (!mark[i]) {
      printf("%lld\n", i + L);
    }
  }
  return 0;
}

#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

using int64 = long long;

const int M = 1e3 + 10, N = 64;

int C[N][N], P[N][N][M], ret[M];
int mod;

void conv(int *a, int *b, int *r, int n){
  static int t[M];
  for (int i = 0; i <= n; ++i) {
    int64 tt = 0;
    for (int j = 0; j <= i; ++j) {
      tt += (int64)a[j] * b[i-j];
    }
    t[i] = tt % mod;
  }
  std::copy(t, t + n + 1, r);
}

int main() {
  int64 n;
  int m, x;
  scanf("%lld%d%d%d", &n, &mod, &m, &x);

  C[0][0] = C[1][0] = C[1][1] = 1;
  for (int i = 2; i < N; ++i) {
    C[i][0] = 1;
    for (int j = 1; j <= (i + 1) / 2; ++j) {
      C[i][j] = (C[i - 1][j] + C[i - 2][j - 1]) % mod;
    }
  }

  std::vector<int64> cnt(N);
  int bound = 0;
  for (; n; n /= x) cnt[++bound] = n;
  for (int it = 0; it < 2; ++it) {
    for (int i = 1; i < bound; ++i) {
      cnt[i] -= cnt[i + 1];
    }
  }
  memset(ret, 0, sizeof(ret));
  ret[0] = 1;
  for (int l = 1; l <= bound; ++l) {
    std::copy(C[l], C[l] + (l + 3) / 2, P[l][0]);
    for (int x = 0; x < N && cnt[l]; ++x, cnt[l] >>= 1) {
      if (cnt[l] & 1) {
        conv(ret, P[l][x], ret, m);
      }
      conv(P[l][x], P[l][x], P[l][x + 1], m);
    }
  }
  printf("%d\n", ret[m]);
  return 0;
}

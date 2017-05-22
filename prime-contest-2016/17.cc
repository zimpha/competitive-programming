#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using ll = long long;

const int N = 15, M = 200, L = 50000 + 10, mod = 1e9 + 7;

int s[N][L], coef[N][N], prob[M];

ll pow_mod(ll a, ll n) {
  ll r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % mod;
    a = a * a % mod;
  }
  return r;
}

int A[N][N], B[N];
void gauss(int n, int a[N][N], int b[N]) {
  for (int k = 0, s; k < n; ++k) {
    for (int i = k; i < n; ++i) {
      if (a[i][k]) s = i;
    }
    for (int i = k; i < n; ++i) {
      std::swap(a[s][i], a[k][i]);
    }
    std::swap(b[s], b[k]);
    for (int j = k + 1; j < n; ++j) {
      ll mul = (mod - a[j][k] * pow_mod(a[k][k], mod - 2) % mod) % mod;
      b[j] = (b[j] + b[k] * mul) % mod;
      for (int i = k + 1; i < n; ++i) {
        a[j][i] = (a[j][i] + mul * a[k][i]) % mod;
      }
    }
  }
  for (int i = n - 1; i >= 0; --i) {
    b[i] = b[i] * pow_mod(a[i][i], mod - 2) % mod;
    for (int j = 0; j < i; ++j) {
      b[j] = (b[j] - (ll)a[j][i] * b[i] % mod + mod) % mod;
    }
  }
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n, m, l;
    scanf("%d%d%d", &n, &m, &l);
    int sum = 0;
    for (int i = 0; i < m; ++i) {
      scanf("%d", &prob[i]);
      sum += prob[i];
    }
    for (int i = 0; i < m; ++i) {
      prob[i] = pow_mod(prob[i], mod - 2) * sum % mod;
    }
    for (int i = 0; i < n; ++i) {
      for (int j = 1; j <= l; ++j) {
        scanf("%d", &s[i][j]);
        --s[i][j];
      }
    }
    for (int i = 0; i < n; ++i) {
      static int fail[L], expect[L];
      for (int j = 2, k = 0; j <= l; ++j) {
        while (k && s[i][k + 1] != s[i][j]) k = fail[k];
        fail[j] = s[i][k + 1] == s[i][j] ? ++k : k;
      }
      expect[0] = 1;
      for (int j = 1; j <= l; ++j) {
        expect[j] = (ll)expect[j - 1] * prob[s[i][j]] % mod;
      }
      expect[0] = 0;
      for (int j = 1; j <= l; ++j) {
        expect[j] += expect[fail[j]];
        if (expect[j] >= mod) expect[j] -= mod;
      }
      for (int j = 0; j < n; ++j) {
        for (int k = 1, t = 0; k <= l; ++k) {
          while (t && s[i][t + 1] != s[j][k]) t = fail[t];
          if (s[i][t + 1] == s[j][k]) ++t;
          if (k == l) coef[i][j] = expect[t];
        }
      }
    }
    int ans = 0;
    for (int msk = 1; msk < (1 << n); ++msk) {
      std::vector<int> candidate;
      for (int i = 0; i < n; ++i) {
        if (msk >> i & 1) candidate.push_back(i);
      }
      int m = candidate.size();
      memset(A, 0, sizeof(A));
      memset(B, 0, sizeof(B));
      for (int i = 0; i < m; ++i) A[m][i] = 1;
      B[m] = 1;
      for (int i = 0; i < m; ++i) {
        A[i][m] = mod - 1;
        for (int j = 0; j < m; ++j) {
          A[i][j] = coef[candidate[i]][candidate[j]];
        }
      }
      gauss(m + 1, A, B);
      if (__builtin_popcount(msk) & 1) {
        ans += B[m];
      } else {
        ans -= B[m];
      }
      ans %= mod;
      if (ans < 0) ans += mod;
    }
    printf("%d\n", ans);
  }
  return 0;
}

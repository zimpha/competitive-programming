#include <cstdio>
#include <vector>

using ll = long long;

std::vector<ll> get_poly() {
  int n;
  scanf("%d", &n);
  std::vector<ll> coef(n + 1);
  for (int i = 0; i <= n; ++i) {
    scanf("%lld", &coef[i]);
  }
  return coef;
}

std::vector<ll> divide(std::vector<ll> A, std::vector<ll> B) {
  int n = A.size() - 1, m = B.size() - 1;
  if (n < m) return {};
  std::vector<ll> C(n - m + 1);
  for (int i = n; i >= m; --i) {
    if (A[i] % B[m]) return {};
    ll e = i - m;
    ll k = A[i] / B[m];
    for (int j = 0; j <= m; ++j) {
      A[i - j] -= k * B[m - j];
    }
    C[e] = k;
  }
  for (int i = 0; i < m; ++i) {
    if (A[i]) return {};
  }
  return C;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    auto G = get_poly();
    auto F = get_poly();
    auto H = divide(G, F);
    printf("Case #%d:", cas);
    if (H.empty()) puts(" no solution");
    else {
      for (auto &&x: H) printf(" %lld", x);
      puts("");
    }
  }
  return 0;
}

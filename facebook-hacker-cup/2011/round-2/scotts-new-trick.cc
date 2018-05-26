#include <cstdio>
#include <vector>
#include <cassert>
#include <algorithm>

using ll = long long;

inline ll mul_mod(ll a, ll b, ll mod) {
  assert(0 <= a && a < mod);
  assert(0 <= b && b < mod);
  if (mod < int(1e9)) return a * b % mod;
  ll k = (ll)((long double)a * b / mod);
  ll res = a * b - k * mod;
  res %= mod;
  if (res < 0) res += mod;
  return res;
}

ll pow_mod(ll a, ll n, ll m) {
  ll r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = mul_mod(r, a, m);
    a = mul_mod(a, a, m);
  }
  return r;
}

ll euler_phi(ll n) {
  ll r = n;
  for (ll i = 2; i * i <= n; ++i) {
    if (n % i == 0) {
      r = r / i * (i - 1);
      while (n % i == 0) n /= i;
    }
  }
  if (n > 1) r = r / n * (n - 1);
  return r;
}

bool test(ll g, ll n, ll phi, std::vector<ll> &u) {
  for (size_t i = 0; i < u.size(); ++i) {
    if (pow_mod(g, phi / u[i], n) == 1) return false;
  }
  return true;
}

ll primitive_root(ll n) {
  ll phi = euler_phi(n), m = phi;
  std::vector<ll> u;
  for (ll i = 2; i * i <= m; ++i) if (m % i == 0) {
    u.push_back(i);
    while (m % i == 0) m /= i;
  }
  if (m > 1) u.push_back(m);
  for (int g = 1; ; ++g) {
    if (test(g, n, phi, u)) return g;
  }
  return -1;
}

namespace NTT {
  static const int W = 1 << 20;
  static const ll P = 1231453023109121ll, g = 3;
  void trans(ll a[], int n, bool inv = false) {
    ll w = 1, d = pow_mod(g, (P - 1) / n, P), t;
    int i, j, c, s;
    if (inv) {
      for (i = 1, j = n - 1; i < j; std::swap(a[i++], a[j--]));
      for (t = pow_mod(n, P - 2, P), i = 0; i < n; ++i) {
        a[i] = mul_mod(a[i], t, P);
      }
    }
    for (s = n >> 1; s; s >>= w = 1, d = mul_mod(d, d, P)) {
      for (c = 0; c < s; ++c, w = mul_mod(w, d, P)) {
        for (i = c; i < n; i += s << 1) {
          t = a[i | s];
          a[i | s] = mul_mod((a[i] + P - t) % P, w, P);
          a[i] = (a[i] + t) % P;
        }
      }
    }
    for (i = 1; i < n; ++i) {
      for (j = 0, s = i, c = n >> 1; c; c >>= 1, s >>= 1) {
        j = j << 1 | s & 1;
      }
      if (i < j) std::swap(a[i], a[j]);
    }
  }
  std::vector<ll> conv(const std::vector<ll> &a, const std::vector<ll> &b) {
    int n = a.size(), s = 1;
    while (s <= (n - 1) * 2) s <<= 1;
    static ll A[W], B[W];
    for (int i = 0; i < s * 2; ++i) {
      A[i] = i < n ? a[i] : 0;
      B[i] = i < n ? b[i] : 0;
    }
    trans(A, s);
    trans(B, s);
    for (int i = 0; i < s; ++i) {
      A[i] = mul_mod(A[i], B[i], P);
    }
    trans(A, s, true);
    std::vector<ll> C(n, 0);
    for (int i = 0; i < s; ++i) {
      C[i % n] += A[i];
    }
    return C;
  }
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int P, L;
    scanf("%d%d", &P, &L);
    int g = primitive_root(P);
    std::vector<int> mapping(P), pw(P, 1);
    for (int i = 1; i < P - 1; ++i) {
      pw[i] = 1ll * pw[i - 1] * g % P;
    }
    for (int i = 0; i < P - 1; ++i) {
      mapping[pw[i]] = i;
    }
    auto gen = [&P, &mapping] (std::vector<ll> &cnt, ll &zero) {
      int n, a1, a2, a3, a4, a5;
      scanf("%d%d%d%d%d%d", &n, &a1, &a2, &a3, &a4, &a5);
      if (a1) cnt[mapping[a1]]++; else zero++;
      if (a2) cnt[mapping[a2]]++; else zero++;
      for (int i = 3; i <= n; ++i) {
        int a = (1ll * a1 * a3 + 1ll * a2 * a4 + a5) % P;
        if (a == 0) zero++;
        else cnt[mapping[a]]++;
        a1 = a2, a2 = a;
      }
      return n;
    };
    std::vector<ll> A(P - 1), B(P - 1);
    ll zero_A = 0, zero_B = 0;
    int n = gen(A, zero_A);
    int m = gen(B, zero_B);
    ll ret = zero_A * m + zero_B * n - zero_A * zero_B;
    auto C = NTT::conv(A, B);
    for (int i = 0; i < P - 1; ++i) {
      if (pw[i] < L) ret += C[i];
    }
    printf("Case #%d: %lld\n", cas, ret);
  }
  return 0;
}
